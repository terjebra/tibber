open Css;

module GetHomes = [%graphql
  {|
  query GetViewer{
    viewer {
      homes {
        id
        appNickname
      }
    }
  }
|}
];

let box =
  style([
    padding(em(2.)),
    border(px(2), solid, rgba(2, 195, 154, 1.)),
    backgroundColor(rgba(2, 195, 154, 1.)),
    marginBottom(em(0.5)),
  ]);

module GetHomesQuery = ReasonApollo.CreateQuery(GetHomes);

let component = ReasonReact.statelessComponent("Homes");

let getId = (home) =>
    home
    -> Belt.Option.mapWithDefault("", home => home##id); 

let getNickname = (home) =>
  home
  -> Belt.Option.flatMap(home => home##appNickname)
  -> Belt.Option.mapWithDefault("", name => name);


let onHomeClick = (id,event) => {
  ReasonReact.Router.push("/homes/" ++ id);
} 

let make = _children => {
  ...component,
  
  render: _self =>
    <GetHomesQuery>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(error) =>
             <Snackbar message=Some(Error(error##message)) />;
             | Data(response) =>
               <div>
               <h2>(ReasonReact.string("Homes"))</h2>
                 (
                   response##viewer##homes
                   |> Js.Array.map(home =>
                        <div key=getId(home)className=box onClick=onHomeClick(getId(home))>
                          <div>
                            (
                              ReasonReact.string(
                                getNickname(home)
                              )
                            )
                          </div>
                        </div >
                      )
                   |> ReasonReact.array
                 )
               </div>
             }
         )
    </GetHomesQuery>,
};