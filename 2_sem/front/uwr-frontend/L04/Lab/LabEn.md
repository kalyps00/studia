# Assignment: Contact Form (10 points)

Your task will be to create a responsive contact form. Unlike previous assignments, in this task, you will independently define **how** the form should look and how responsiveness will be implemented. You can use Flexbox, Grid, media queries, or approach the problem in a completely different way. The design can have several different versions or be entirely fluid. The chosen solution should, of course, be justified: list its advantages and disadvantages.

Although the task is quite open, below are guidelines defining the minimum requirements that the form must meet.

## Example

Example solution: [Full Size](./form_fullsize.png) ([high resolution](./form_fullsize_fullres.png)), [Small Size](./form_smallsize_fullres.png), [Phone](./form_phone_fullres.png), [Large Font](./form_bigfont.png) ([high resolution](./form_bigfont_fullres.png)).

## Materials

For this task, materials on [Grid](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Grid_Layout), [Flexbox](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox), and a [guide on macro layouts](https://web.dev/learn/design/macro-layouts/) may prove useful. Additionally, some forms will require writing simple validation. For this, a [regex editor](https://regex101.com/) may come in handy.

## Requirements

1. Styles should be easy to manage and readable for other developers. To achieve this, use one of the popular methodologies (e.g., BEM). Try to ensure that all styled elements have an appropriate class (unless you believe that using a different selector makes more sense in a given situation).
2. The form should be placed on a "card," maintaining appropriate margins from the screen edges, depending on the available space.
3. The form should include:
   1. A header, which is a text
   2. First name (required) - text field
   3. Last name - text field
   4. Email (required) - text field
   5. Phone - text field
   6. Newsletter subscription - checkbox
   7. Reason for contact (required) - dropdown with several options (can be arbitrary)
   8. Message (required) - text area, but appropriately larger
   9. A "submit" button that sends the form
4. The form should be properly structured. Each field should include a label, input fields should have appropriate types, and the form itself should be placed in the appropriate tag.
5. The "submit" button should be appropriately large and attention-grabbing.
6. The font size should depend on the user's device width. It should also respect the user's preferred font size but should not grow too large.

   <details>
     <summary>Hint</summary>

   > While responsive fonts are not standard, in this task, we primarily want to explore possibilities. The most standard way to make font size dependent on the device size is to use an appropriate unit (`vw`, `vh`, `vmin`, `vmax`: which is best here?) and set the main font size (the one in the `html` tag) to an appropriate value.
   >
   > To respect the user's preferences, we can use the `calc` function and add a relative unit, e.g., `rem`.
   >
   > To prevent the font from growing too large, we can use the `clamp` function.
   >
   > You may need: https://www.smashingmagazine.com/2022/01/modern-fluid-typography-css-clamp/

   </details>

7. If the user is viewing the form on a touch device, the `checkbox` field might be difficult to select. Since we really want the user to be able to select it easily, on such devices, the checkbox should be slightly larger. _Note:_ In this task, you **cannot** assume that a mobile device is one with a sufficiently small screen: you must find another solution.

   <details>
     <summary>Hint</summary>

   > [This might be useful](https://developer.mozilla.org/en-US/docs/Web/CSS/@media/pointer)

   </details>

8. The form should be validated:

   1. Required fields should indeed be required.
   2. The Email field should require a valid email address. For this task, we can assume that a valid email address consists of a sequence of characters, an "@" symbol, another sequence of characters, a dot, and another sequence of characters.

      <details>
        <summary>Hint</summary>

      > The problem of validating an email address is surprisingly complex. There are [complex regular expressions](http://www.ex-parrot.com/~pdw/Mail-RFC822-Address.html) that solve this problem, but rewriting them into HTML might be tedious. "A sequence of characters" in the description is intentionally vague: define it in a way that makes sense. The goal of the task is not to check if you can write a complex regular expression.
      >
      > The `pattern` attribute might be useful.

      </details>

   3. The Phone field should require a valid phone number. We can assume that all phone numbers we are interested in consist of 9 digits (and only digits).
   4. All fields filled incorrectly should provide appropriate visual feedback, e.g., by highlighting the border in red.

      <details>
        <summary>Hint</summary>

      > The `:invalid` pseudo-class might be very useful.

      </details>

9. The form should be responsive:
   1. The number of columns should vary depending on the available space. If there is more space, there should be more columns; if there is less space, there can be fewer columns.
   2. The page should not "break." At some point, the card should not be able to shrink further. This size should depend on the user's font size. This means that with any font size and on any screen, the form should look good, even if it means showing a scrollbar.
   3. The size of the checkbox should also depend on the user's font size.
