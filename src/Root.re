/* Due to ease of use with ParcelJs these are in a css file
   Left here to show how to use fonts

   let light =
       Css.(
         fontFace(
           ~fontFamily="Open Sans",
           ~fontStyle=normal,
           ~fontWeight=300,
           ~src=[
             Css.localUrl("Open Sans Light"),
             Css.localUrl("OpenSans-Light"),
             Css.url("./fonts/open-sans-v15-latin-300.woff2"),
             Css.url("./fonts/open-sans-v15-latin-300.woff"),
           ],
           (),
         )
       );

     let regular =
       Css.(
         fontFace(
           ~fontFamily="Open Sans",
           ~fontStyle=normal,
           ~fontWeight=400,
           ~src=[
             Css.localUrl("Open Sans Regular"),
             Css.localUrl("OpenSans-Regular"),
             Css.url("./fonts/open-sans-v15-latin-regular.woff2"),
             Css.url("./fonts/open-sans-v15-latin-regular.woff"),
           ],
           (),
         )
       );

     let bold =
       Css.(
         fontFace(
           ~fontFamily="Open Sans",
           ~fontStyle=normal,
           ~fontWeight=700,
           ~src=[
             Css.localUrl("Open Sans Bold"),
             Css.localUrl("OpenSans-Bold"),
             Css.url("./fonts/open-sans-v15-latin-700.woff2"),
             Css.url("./fonts/open-sans-v15-latin-700.woff"),
           ],
           (),
         )
       ); */
Css.(
  global(
    "body",
    [
      /* fontFamily(light),
         fontFamily(regular),
         fontFamily(bold), */
      margin(px(0)),
      color(hex("FDFDF9")),
      backgroundColor(rgba(47, 127, 160, 1.)),
      fontSize(Calc.(em(0.5) + vw(1.0))),
    ],
  )
);

Css.(global("a, a:visited", [color(hsla(167, 98, 39, 1.))]));

Css.(global("a:active", [color(hsla(347, 98, 39, 1.))]));

open AppContext;

type state = {
  token: option(string),
  client: option(ApolloClient.generatedApolloClient),
  message: option(message),
};

type action =
  | UpdateToken(string)
  | ShowMessage(option(message));

let saveToken = token => Storage.saveToken(token);

let component = ReasonReact.reducerComponent("Root");

let getToken = token =>
  if (String.length(token) > 0) {
    Some(token);
  } else {
    None;
  };

let make = _children => {
  ...component,
  initialState: () => {
    token: Storage.getToken(),
    client:
      switch (Storage.getToken()) {
      | Some(token) => Some(Client.createInstance(token))
      | None => None
      },
    message: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateToken(token) =>
      let tokenToUpdate = getToken(token);
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          token: tokenToUpdate,
          client:
            switch (tokenToUpdate) {
            | Some(token) => Some(Client.createInstance(token))
            | None => None
            },
        },
        (
          _self =>
            switch (tokenToUpdate) {
            | Some(token) => saveToken(token)
            | _ => ()
            }
        ),
      );
    | ShowMessage(message) => ReasonReact.Update({...state, message})
    },
  render: ({state, send}) =>
    <AppContext.Provider
      value={
        token: state.token,
        client: state.client,
        updateToken: token => send(UpdateToken(token)),
        message: state.message,
        showMessage: (message: option(message)) =>
          send(ShowMessage(message)),
      }>
      (
        switch (state.client) {
        | Some(client) =>
          <ReasonApollo.Provider client>
            <Page />
            <Snackbar message=state.message />
          </ReasonApollo.Provider>
        | None =>
          <Welcome onRegisterClicked=(text => UpdateToken(text) |> send) />
        }
      )
    </AppContext.Provider>,
};