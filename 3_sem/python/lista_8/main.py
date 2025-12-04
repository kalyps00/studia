import requests
import matplotlib.pyplot as plt
import pandas as pd
from datetime import datetime, timedelta


api_url = "https://api.nbp.pl/api/"


def process_data(df: pd.DataFrame):

    pass


def fetch_gold_price(year: int):

    data = []
    start_date = datetime.strptime(f"{year}-01-01", "%Y-%m-%d")
    end_date = datetime.strptime(f"{year}-12-31", "%Y-%m-%d")
    current_start = start_date
    while current_start < end_date:
        current_end = min(current_start + timedelta(days=93), end_date)
        s_str = current_start.strftime("%Y-%m-%d")
        e_str = current_end.strftime("%Y-%m-%d")
        try:
            response = requests.get(f"{api_url}cenyzlota/{s_str}/{e_str}", timeout=10)
            response.raise_for_status()
            data.extend(response.json())
        except Exception as e:
            print(f"exception during fetching data: {e}")
        current_start = current_end + timedelta(days=1)

    df = pd.DataFrame(data)
    process_data(df)
    return df


def fetch_exchange_rates(year: int, currency_code: str):

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
                f"{api_url}exchangerates/rates/A/{currency_code}/{s_str}/{e_str}/",
                timeout=10,
            )
            response.raise_for_status()
            data.extend(response.json().get("rates", []))
        except Exception as e:
            print(f"exception during fetching data: {e}")
        current_start = current_end + timedelta(days=1)

    df = pd.DataFrame(data)
    process_data(df)
    return df
