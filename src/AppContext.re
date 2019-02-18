type message =
  | Information(string)
  | Error(string);

type contextType = {
  token: option(string),
  message: option(message),
  client: option(ApolloClient.generatedApolloClient),
  updateToken: string => unit,
  showMessage: option(message) => unit,
};

module AppContext =
  Context.MakePair(
    {
      type t = contextType;
      let defaultValue = {
        token: Storage.getToken(),
        message: None,
        client:
          switch (Storage.getToken()) {
          | Some(token) => Some(Client.createInstance(token))
          | None => None
          },
        updateToken: (_) => (),
        showMessage: (_) => (),
      };
    },
  );