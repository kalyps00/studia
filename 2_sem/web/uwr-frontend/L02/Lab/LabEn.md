# Task: Page Styling (10p)

Your task is to style the page according to the guidelines below. The styling should be implemented **exclusively using CSS**. You may edit the HTML code only in the designated areas marked by comments. The final appearance of the page should match the [image](./sol.png) ([full resolution](./sol_fullres.png)).

You can find HTML file [here](https://github.com/Arsenicro/uwr-frontend/blob/main/L02/Lab/challenges.html). Your solutions should be inside [style.css](./style.css) file.

## Resources

In addition to the resources available on [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS), it is recommended to practice selectors and specificity using [CSS Dinner](https://flukeout.github.io/) and [CSS Speedrun](https://css-speedrun.netlify.app/).

The reference solution uses the following properties:  
`background-color`, `border`, `border-color`, `border-radius`, `border-top`, `border-top-color`, `box-sizing`, `color`, `content`, `display`, `font-family`, `font-size`, `font-weight`, `list-style`, `margin`, `max-width`, `min-width`, `text-align`, `text-decoration`, `width`.

---

## **Global Styling**: Applied to the entire page

- Set the page background color to `lightblue` and the text color to `darkblue`.
- Choose any font from [Google Fonts](https://fonts.google.com/) and apply it to the entire page. To do this, add the appropriate link to the HTML file's `<head>` section.
- All `h1` headings should have a font-weight of `800`.
- Paragraphs (`<p>`) should have margins on all sides – the right and left margins should be equal and greater than zero. The margins should increase proportionally with the font size of the `html` element.
- Set the default font size to `1rem`.
- The `h1` header should be horizontally centered.

## **Boxes**: "Boxes" Section (`id="challenge2"`)

- The `"boxes"` section contains three boxes:

  - **The first box** should be `lightgreen` and circular.
  - **The second box** should be `lightslategray` with a black border of `10px` thickness. Including the border, it should have a `100px x 100px` size.
  - **The third box** should be half white (top) and half red (bottom).

- Hover interactions ([gif](./hover.gif)):

  - **The first box** should change color to `lightpink` when hovering.
  - **The second box** should have a black center and a `lightslategray` border on hover.
  - **The third box** should swap colors on hover (top red, bottom white).

- **To receive full points, do not directly modify the height or width of the boxes.**

## **Link Styling**: "Links" Section (`id="challenge3"`)

- Links should have the same color as the text (`darkblue`).
- Visited links should appear `lightslategray`.
- Links should always be underlined.
- On hover, links should turn red and become bold.
- Instead of bullet points, list items should use the "🍔" icon.

## **Hiding Elements**: "Too much" Section (`id="challenge4"`)

Hide the following elements:

- Empty paragraphs (`<p></p>`).
- Disabled (`disabled`) `<input>` fields.
- Links containing `"recipe"` in the URL.

The hiding should also apply to newly added elements and not depend on their order in the code.

## **Responsive Image**: "Images" Section (`id="challenge5"`)

- The image width should be **70% of the available space**.
- Minimum width: `100px`.
- Maximum width: `500px`.
- The caption under the image (`<figcaption>`) should have a font size of **`0.7`** times the font size of the `html` element.
