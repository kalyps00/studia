# Task: Todo List (10 points)

In this task, you will extend an existing TODO list with functionality by adding appropriate scripts. You will find all the files in the [todo-list](./todo-list/) folder. Modifying other files is allowed, not just the sample data (which may need to be removed).

The sample data presents the structure of the added elements. Additionally, specific information about the required classes for certain elements will be included in the content below.

The task can be done in two ways: relying entirely on the "state" of the elements, or by creating an additional array that stores the list of todo elements and a `render` function that will prepare the appropriate page structure based on this list. Choose one of these two approaches. The instructor has the right to ask for a justification of your choice.

## Materials

The following methods may be useful:

- [getElementById](https://developer.mozilla.org/en-US/docs/Web/API/Document/getElementById)
- [querySelector](https://developer.mozilla.org/en-US/docs/Web/API/Document/querySelector)
- [addEventListener](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener)
- [preventDefault](https://developer.mozilla.org/en-US/docs/Web/API/Event/preventDefault)
- General knowledge about [Elements](https://developer.mozilla.org/en-US/docs/Web/API/Element).

## Requirements

- The todo list should allow adding items.
  - Adding items should be done through a `form`.
  - A new item should be added as an `li` to the `ul` element (id: `todo-list`).
  - The `li` element should have the class `todo__container`.
  - A completed task `li` element should also have the class `todo__container--completed`.
  - Inside the `li` element, there will be components:
    - Each one will have the class `todo-element`.
    - Additionally, each button will have the class `todo-button`.
    - Specification of the components:
      - The component storing the name should be a `div`, with the additional class `todo-name`.
      - The up/down movement buttons should additionally have appropriate classes (`move-up` and `move-down`). **You do not need** to ensure that the up button does not appear for the first item, and the down button does not appear for the last item. CSS takes care of that.
      - The `Done` button should appear only for incomplete items, and the `Revert` button should appear only for completed items.
      - The Remove button should be present.
- The todo list should allow removing an item from the list using the `Remove` button.
- The todo list should allow marking an item as completed using the `Done` button.
- The todo list should allow marking an item as incomplete using the `Revert` button.
- The counter at the top of the list (`Todo List (4 remaining)`) should always display the number of tasks remaining to be completed (tasks that are not marked as completed).
- The "Clear All" button should allow completely clearing the list (removing all items).
- The "Up" and "Down" buttons should allow swapping the positions of the corresponding items.
