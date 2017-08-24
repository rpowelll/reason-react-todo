type state = {
  items: list Item.item,
  filter: Filter.filter
};

type self = ReasonReact.self state ReasonReact.noRetainedProps;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statefulComponent "TodoApp";

let addItem text ({state}: self) => {
  ReasonReact.Update {
    ...state,
    items: Item.addItem state.items text
  };
};

let toggleItem ({id}: Item.item) ({state}: self) => {
  ReasonReact.Update {
    ...state,
    items: Item.toggleCompletion state.items id
  }
};

let setFilter filter ({state}: self) =>
  ReasonReact.Update {
    ...state,
    filter: filter
  };

let renderItem update (item: Item.item) =>
    <TodoItem
      item
      onToggle=(update toggleItem)
      key=(string_of_int item.id) />;

let renderItemList update items =>
  items
  |> List.map (renderItem update)
  |> Array.of_list
  |> ReasonReact.arrayToElement;

let make _children => {
  ...component,
  initialState: fun () => {
    items: [{
      id: 0,
      title: "Write some things to do",
      completed: false
    }],
    filter: All
  },
  render: fun {state: {items, filter}, update} => {
    let filteredItems = Item.filterItems filter items;
    <div className="app">
      <div className="title">
        (se "What to do")
        <Input onSubmit=(update addItem) />
        <FilterBar
          activeFilter=(filter)
          onChange=(update setFilter) />
      </div>
      <div className="items"> (renderItemList update filteredItems) </div>
      <div className="footer">
        (se (Item.itemCount filteredItems))
      </div>
    </div>
  }
};
