import asyncio
import aiohttp
from private import API_KEY


CATFACT_URL = "https://catfact.ninja/fact"
JOKE_URL = "https://api.api-ninjas.com/v1/dadjokes"


async def fetch_cat_fact(session):
    try:
        async with session.get(
            CATFACT_URL, timeout=aiohttp.ClientTimeout(total=10)
        ) as response:
            if response.status == 429:
                return "Too many requests"
            response.raise_for_status()
            data = await response.json()
            return data["fact"]
    except Exception as e:
        return f"Błąd pobierania faktu o kotach: {e}"


async def fetch_joke(session):
    try:
        headers = {"X-Api-Key": API_KEY}
        async with session.get(
            JOKE_URL, headers=headers, timeout=aiohttp.ClientTimeout(total=10)
        ) as response:
            if response.status == 429:
                return "Too many requests"
            response.raise_for_status()
            data = await response.json()
            return data[0]["joke"]
    except Exception as e:
        return f"Błąd pobierania żartu: {e}"


async def main():
    async with aiohttp.ClientSession() as session:
        cat_fact, joke = await asyncio.gather(
            fetch_cat_fact(session), fetch_joke(session)
        )

        print("=== Fakt o kotach ===")
        print(cat_fact)

        print("\n=== Żart ===")
        print(joke)


if __name__ == "__main__":
    asyncio.run(main())
