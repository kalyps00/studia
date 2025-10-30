/**
 * @typedef {Object} Product
 * @property {number} id - Id produktu.
 * @property {string} name - Nazwa produktu.
 * @property {number} quantity - Liczba sztuk do zakupienia.
 * @property {Date} purchaseDate - Data, do której produkt powinien być zakupiony.
 * @property {boolean} purchased - Status informujący, czy produkt został zakupiony.
 * @property {number} [price] - Opcjonalna cena za sztukę (dotyczy tylko zakupionych produktów).
 */

/**
 * Lista produktów.
 * @type {Product[]}
 */
let products_list = [];
/**
 * funkcja dodajaca produkt
 *
 * @param {string} name
 * @param {number} quantity
 * @param {string} date
 *
 */
function add_product(name, quantity, date) {
  let product_new = {
    id: Math.floor(Math.random() * 1e6),
    name: name,
    quantity: quantity,
    purchaseDate: new Date(date),
    purchased: false,
  };
  products_list.push(product_new);
}
/**
 *funckja usuwajaca produkt
 * @param {number} id
 */

function delete_product(id) {
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1) {
    products_list.splice(index, 1); /* od indexu, ile */
  }
}
/* products_list = products_list.filter(product => product.id!==id) */

/**
 *funkcja zmieniajaca nazwe produktu
 * @param {number} id
 * @param {string} new_name
 */
function change_product_name(id, new_name) {
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1) {
    products_list[index].name = new_name;
  }
}
/**
 * funkcja zmieniajaca ilosc produktu
 * @param {number} id
 * @param {number} new_quantity
 *
 */
function change_product_quantity(id, new_quantity) {
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1) {
    products_list[index].quantity = new_quantity;
  }
}
/**
 * funkcja zmieniajaca date produktu
 * @param {number} id
 * @param {string} new_date
 *
 */
function change_product_date(id, new_date) {
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1) {
    products_list[index].purchaseDate = new Date(new_date);
  }
}
/**
 *dunckja zmieniajaca status zakupu
 * @param {number} id
 * @param {string} purchased
 */
function change_product_purchased(id, purchased) {
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1) {
    products_list[index].purchased = purchased;
  }
}
/**
 * funkcja zmieniajaca produkty miejcami
 * @param {number} id
 * @param {string} new_id
 */
function move_product(id, new_index) {
  let index = products_list.findIndex((product) => product.id === id);
  let temp = products_list[new_index];
  products_list[new_index] = products_list[index];
  products_list[index] = temp;
}
/**
 * funkcja zwracajaca produkty ktorych data konczy sie dzisiaj
 * @returns {Product[]}
 */
function last_day_to_purchase() {
  let last_day = new Date().toDateString(); /* zeby nie bylo milisekund */
  let list = products_list.filter(
    (product) =>
      product.purchaseDate.toDateString() === last_day && !product.purchased
  );
  return list;
}
/**
 * funkcja zmieniajaca cene produktu
 * @param {number} id
 * @param {number} price
 */
function change_bought_price(id, price) {
  if (price < 0) return;
  let index = products_list.findIndex((product) => product.id === id);
  if (index !== -1 && products_list[index].purchased) {
    products_list[index].price = price;
  }
}
/**
 * Oblicza całkowity koszt zakupów danego dnia.
 * @param {string} date - Data w formacie YYYY-MM-DD.
 * @returns {number} - Łączny koszt zakupów.
 */
function calculate_total_price(date) {
  const targetDate = new Date(date).toDateString(); // Konwersja stringa na datę
  return products_list.reduce((total, product) => {
    if (
      product.purchased &&
      product.purchaseDate.toDateString() === targetDate
    ) {
      return total + product.price; /* * product.quantity */
    }
    return total;
  }, 0);
}
/**
 * Funkcja zmienia produkty
 * @param {number[]} id_list
 * @param {function} callback
 */
function chane_products(id_list, callback) {
  products_list = products_list.map((product) => {
    if (id_list.includes(product.id)) {
      return callback(product);
    }
    return product;
  });
}

// Dodawanie produktów
add_product("Chleb", 2, "2025-04-02");
add_product("Mleko", 1, "2025-04-02");
add_product("Masło", 3, "2025-04-03");
add_product("Kupic_dzisiaj", 3, new Date().toDateString());
console.log("Lista produktów po dodaniu:");
console.table(products_list);

// Usuwanie produktu
delete_product(products_list[1].id);

console.log("Lista produktów po usunięciu drugiego produktu:");
console.table(products_list);

// Zmiana nazwy produktu
change_product_name(products_list[0].id, "Bułki");

console.log("Lista produktów po zmianie nazwy pierwszego produktu:");
console.table(products_list);

// Zmiana ilości produktu
change_product_quantity(products_list[0].id, 5);

console.log("Lista produktów po zmianie ilości pierwszego produktu:");
console.table(products_list);

// Zmiana daty zakupu produktu
change_product_date(products_list[0].id, "2025-04-05");

console.log("Lista produktów po zmianie daty zakupu pierwszego produktu:");
console.table(products_list);

// Oznaczenie produktu jako zakupionego
change_product_purchased(products_list[0].id, true);

console.log(
  "Lista produktów po oznaczeniu pierwszego produktu jako zakupionego:"
);
console.table(products_list);

// Ustawienie ceny dla zakupionego produktu
change_bought_price(products_list[0].id, 4.99);

console.log("Lista produktów po ustawieniu ceny dla pierwszego produktu:");
console.table(products_list);

// Obliczanie całkowitego kosztu zakupów dla danego dnia
const totalPrice = calculate_total_price("2025-04-05");
console.log("Całkowity koszt zakupów dla dnia 2025-04-05: ");
console.log(totalPrice);

// Pobranie produktów, które należy zakupić dzisiaj
const lastDayProducts = last_day_to_purchase();
console.log("Produkty, które należy zakupić dzisiaj:");
console.table(lastDayProducts);

// Zmiana kolejności produktów
move_product(products_list[0].id, 1);

console.log("Lista produktów po zmianie kolejności:");
console.table(products_list);

// Masowe formatowanie produktów
chane_products([products_list[0].id], (product) => {
  product.name = product.name.toUpperCase();
  return product;
});
console.log("Lista produktów po masowym formatowaniu:");
console.table(products_list);
