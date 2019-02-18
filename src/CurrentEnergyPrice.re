/* Create a GraphQL Query by using the graphql_ppx */
module GetCurrentSubscription = [%graphql
  {|
  query GetViewer{
    viewer {
      homes {
        id
        currentSubscription {
          priceInfo {
            current {
              total
              startsAt
              currency
            }
          }
        }
      }
    }
  }
|}
];

module GetCurrentSubscriptionQuery =
  ReasonApollo.CreateQuery(GetCurrentSubscription);

let component = ReasonReact.statelessComponent("CurrentEnergyPrice");
let getCurrency = (home) =>
    home
    -> Belt.Option.flatMap(home => home##currentSubscription)
    -> Belt.Option.flatMap(currentSubscription => currentSubscription##priceInfo)
    -> Belt.Option.flatMap(priceInfo => priceInfo##current)
    -> Belt.Option.mapWithDefault("", current => current##currency); 

let getTotal = (home) =>  
    home
    -> Belt.Option.flatMap(home => home##currentSubscription)
    -> Belt.Option.flatMap(currentSubscription => currentSubscription##priceInfo)
    -> Belt.Option.flatMap(priceInfo => priceInfo##current)
    -> Belt.Option.flatMap(current => current##total)
    -> Belt.Option.mapWithDefault(0.0, total => total);

let getStartsAt = (home) =>
  home
  -> Belt.Option.flatMap(home => home##currentSubscription)
  -> Belt.Option.flatMap(currentSubscription => currentSubscription##priceInfo)
  -> Belt.Option.flatMap(priceInfo => priceInfo##current)
  -> Belt.Option.flatMap(current => current##startsAt)
  -> Belt.Option.mapWithDefault(Js.Date.toDateString(Js.Date.make()), startsAt => startsAt);


let getId = (home) =>
  home
  -> Belt.Option.mapWithDefault("", home => home##id)

let make = _children => {
  ...component,
  render: _self =>
  <GetCurrentSubscriptionQuery>
  ...(
      ({result, refetch}) =>
        switch (result) {
        | Loading => <div> (ReasonReact.string("Loading")) </div>
        | Error(error) =>
          <Snackbar message=Some(Error(error##message)) />;
        | Data(response) =>
          (
              response##viewer##homes
              |> Js.Array.map(home => 
                <LiveCurrentEnergyPrice key=(getId(home)) onPriceElapsed=(
                  ((_) => {
                    refetch(None)  |> ignore;
                  })
                ) text=(string_of_float(getTotal(home)*. 100.0)) subText=({js|øre|js}) startsAt=getStartsAt(home) />
              )
              |> ReasonReact.array
          )
        }
    )
</GetCurrentSubscriptionQuery>
};