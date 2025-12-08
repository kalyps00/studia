import requests
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from numpy.polynomial import Polynomial
from datetime import datetime, timedelta


api_url = "https://api.nbp.pl/api/exchangerates/"


def process_data(df: pd.DataFrame) -> pd.Series:
    if df.empty:
        return pd.Series(dtype="float64")
    df["effectiveDate"] = pd.to_datetime(df["effectiveDate"])
    df.set_index("effectiveDate", inplace=True)
    return df["mid"].resample("ME").mean()


def fetch_exchange_rates(year: int, currency_code: str) -> pd.Series:
    data = []
    start_date = datetime.strptime(f"{year}-01-01", "%Y-%m-%d")
    end_date = datetime.strptime(f"{year}-12-31", "%Y-%m-%d")
    current_start = start_date
    while current_start < end_date:
        current_end = min(current_start + timedelta(days=93), end_date)
        s_str = current_start.strftime("%Y-%m-%d")
        e_str = current_end.strftime("%Y-%m-%d")
        try:
            response = requests.get(
                f"{api_url}rates/A/{currency_code}/{s_str}/{e_str}/",
                timeout=10,
            )
            response.raise_for_status()
            data.extend(response.json().get("rates", []))
        except Exception as e:
            print(f"exception during fetching data: {e}")
        current_start = current_end + timedelta(days=1)

    df = pd.DataFrame(data)
    return process_data(df)


# regresja liniowa ważona
def predict_rates(history_series: pd.Series) -> np.ndarray:
    if history_series.empty:
        return np.zeros(12)
    y = history_series.to_numpy(dtype=float)
    x = np.arange(len(y))
    weights = np.linspace(0.1, 1.0, len(y))
    p = Polynomial.fit(x, y, deg=1, w=weights)
    future_x = np.arange(len(x), len(x) + 12)
    return p(future_x)


if __name__ == "__main__":
    years = [2020, 2021]
    currency_codes = ["TRY", "ZAR", "USD"]  # Lira turecka, Rand południowoafrykański
    all_history = {code: pd.Series(dtype="float64") for code in currency_codes}
    fig, axes = plt.subplots(1, len(years) + 1, figsize=(18, 6))
    fig.suptitle(
        "Average Monthly Exchange Rates in 2022 and 2023 and 2024 prediction",
        fontsize=16,
    )
    for year, ax in zip(years, axes):
        ax.set_title(f"Year {year}")
        ax.set_xlabel("Month")
        ax.set_ylabel("Exchange Rate (PLN)")
        for code in currency_codes:
            rates = fetch_exchange_rates(year, code)
            if not rates.empty:
                if all_history[code].empty:
                    all_history[code] = rates
                else:
                    all_history[code] = pd.concat([all_history[code], rates])
                ax.plot(
                    pd.DatetimeIndex(rates.index).month,
                    rates.values,
                    marker="o",
                    label=code,
                )

        ax.legend()
        ax.grid(True)
        ax.set_xticks(range(1, 13))

    ax_pred = axes[len(years)]
    ax_pred.set_title("Prediction 2024")
    ax_pred.set_xlabel("Month")
    ax_pred.set_ylabel("Exchange Rate (PLN)")

    months_pred = range(1, 13)

    for code in currency_codes:
        predicted_values = predict_rates(all_history[code])
        ax_pred.plot(
            months_pred,
            predicted_values,
            marker="o",
            label=code,
        )

    ax_pred.legend()
    ax_pred.grid(True)
    ax_pred.set_xticks(range(1, 13))

    plt.tight_layout()
    fig.subplots_adjust(top=0.9)
    plt.show()
