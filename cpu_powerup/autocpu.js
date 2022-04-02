const { Api, JsonRpc, RpcError } = require("eosjs");
const { JsSignatureProvider } = require("eosjs/dist/eosjs-jssig"); // development only
const fetch = require("node-fetch"); // node only; not needed in browsers
const { TextEncoder, TextDecoder } = require("util"); // node only; native TextEncoder/Decoder
// const { TextEncoder, TextDecoder } = require('text-encoding');  // React Native, IE11, and Edge Browsers only

const defaultPrivateKey = "PVT_K1_26fMPzM27mXhoSF8y56ro7pN2te7rFT6W6wXiUi5joY79NHfZf"; 
const signatureProvider = new JsSignatureProvider([defaultPrivateKey]);
const rpc = new JsonRpc("http://api.eosflare.io", { fetch });


const api = new Api({
  rpc,
  signatureProvider,
  textDecoder: new TextDecoder(),
  textEncoder: new TextEncoder(),
}); 

(async()=>{
  let actions =  [
    { account: "eosio",
      name: "powerup",
      authorization: [{ actor: "zijunzimo555",permission: "active",}],
      data: {  
      "payer": "zijunzimo555",
      "receiver": "zijunzimo555",
      "days": 1,
      "net_frac": 3000,
      "cpu_frac": 348661516,
      "max_payment": "0.0050 EOS"},
    },
  ]
  let seActions = await api.serializeActions(actions)   
  console.log(seActions[0].data)
})()



  



