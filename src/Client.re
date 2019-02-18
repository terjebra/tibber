let config = Config.Config.getConfig();

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let headers = {|{
    "authorization": "Bearer 1716e5f0d0f731a58409e9821e620bfa5a0472fa34616e0cae5cd219d6d27634"
  } |};

let contextHandler = (token, ()) => {
  "headers": {
    "authorization": "Bearer " ++ token,
  },
};

let contextLink = token =>
  ApolloLinks.createContextLink(contextHandler(token));

/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri=config.apiUrl, ());

let createInstance = token =>
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|contextLink(token), httpLink|]),
    ~cache=inMemoryCache,
    (),
  );