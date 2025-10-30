# Task: Shopping List (10p)

Your task is to create functions responsible for the operation of a shopping list. You will use only JavaScript, but the functions you write may later be used to create a full frontend page.

For this task, you do not need to implement communication with the user – it is enough to be able to call functions with appropriate arguments.

In the lecture related to this task, we have not yet discussed the syntax of **arrow functions** (_arrow functions_). You can use them, but remember that the instructor may ask about the differences between them and the methods learned in the lecture.

## Materials

As usual, [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide) may be useful for this task. A good source for learning JavaScript is also [javascript.info](https://javascript.info/) (however, remember that in the first lecture we covered only some topics). In this task, you will mainly work with functions and arrays, so it is worth reading the [function overview](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Functions) and the [documentation of array methods](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array). Particularly useful will be `Array.prototype.push`, `Array.prototype.filter`, `Array.prototype.findIndex`, `Array.prototype.splice`, `Array.prototype.reduce`, `Array.prototype.map`, `Array.prototype.includes`, and `Date.prototype.toDateString`.

## List of Requirements

1. Each function you write should be documented using [jsDoc](https://jsdoc.app/index.html).
1. At the top of the file, define a variable storing the list of products, initially empty.
   - Define (in jsDoc) the `Product` type describing a product object:
     - Product id (`number`)
     - Name (`string`)
     - Number of items to purchase (`number`)
     - Date by which the product should be purchased ([Date object](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date))
     - Status indicating whether the product has been purchased (`boolean`)
     - Optional price per unit (applies only to purchased products)
   - Assign the variable the type of an array of `Product` objects.
1. Add a function that allows adding a new product to the list.
   - The function should not accept an `id` – it should generate one.
     - You can assume that a random number from a large range will be sufficiently unique.
   - The function should not accept a `Date` object – it should create a date based on the given `string` (we assume the correct format).
1. Add the ability to remove a product from the list based on `id`.
1. Add the ability to edit (based on `id`) the name, status, number of items, and purchase date of a product.
   1. Each field should be editable in a separate function that edits only that one field.
1. Add the ability to change the order of products in the list.
   - The method of changing the order is up to you – for example, you can allow moving elements up/down, swapping places, or moving them to any position.
1. Add a function that returns a list of products that should be purchased today (unpurchased products with today's purchase date).
1. Add the ability to enter a price for purchased products.
   - If the product is not marked as purchased, the function should not change anything.
   - Ensure that it is not possible to assign a price to a product that is not purchased (in what situations could this happen?).
1. Add a function that calculates the cost of purchases on a given day.
   - The function should not accept a `Date` object – it should create a date based on the given `string` (we assume the correct format).
   - The function should work even when not all purchased products have a given price. Determine how it should behave in such cases.
1. Add a function enabling bulk formatting of the shopping list.

   - The function should accept a list of `id` products to be modified and a modifying function.
   - You can determine the format of the modifying function yourself – describe it in a comment.
   - In the future, it should be possible to pass a function, e.g., converting product prices, and apply it to selected elements of the list.

   <details>
     <summary>Hint</summary>

   > In JavaScript, you can pass functions as arguments to other functions. Such a function is called a `callback`.
   >
   > There are array methods that allow performing operations on each element and returning a new array. It is enough to apply the function passed as a parameter to elements with the appropriate `id` (the rest remain unchanged).

   </details>

1. Prepare a list of function calls that will present the appropriate functionalities.
