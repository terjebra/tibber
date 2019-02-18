ReactDOMRe.renderToElementWithId(<Root />, "root");

/* ReasonReact.Router.push calls the pushState browser API which */
/* when given an empty url will push the current url */
ReasonReact.Router.push("");

/*
 HMR
 https://blog.manifold.co/building-reason-react-with-parcel-bundler-cb651278bf47
 */
type parcelModule;

type hot;

[@bs.val] external parcelModule : parcelModule = "module";

[@bs.get] external hot : parcelModule => Js.nullable(hot) = "hot";

[@bs.send.pipe: hot] external accept : unit => unit = "accept";

switch (Js.Nullable.toOption(parcelModule |> hot)) {
| Some(h) => h |> accept()
| _ => Js.log("We are not hot")
};