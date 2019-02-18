let handleClick = (href, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReact.Router.push(href);
};

let component = ReasonReact.statelessComponent("Link");

let make = (~href, children) => {
  ...component,
  render: _self => <a href onClick=(handleClick(href))> ...children </a>,
};