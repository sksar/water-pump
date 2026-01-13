import { writable } from "svelte/store";

export const pump = writable({});

setInterval(poll, 1000);
function poll() {
    rpc("state").then(pump.set).catch(console.error);
}



// ----------------------------------------------------------------------------------

const DEV_URL = "http://water-pump.local"
const PROD_URL = "/";
const WS_URL = import.meta.env.DEV ? DEV_URL : PROD_URL;

const et = new EventTarget();
let ws = new WebSocket(null);

connect();
function connect() {
    ws = new WebSocket(`${WS_URL}/rpc`);
    ws.addEventListener("open", () => {
        console.log("Connected to pump via websocket");
    });
    ws.addEventListener("close", () => setTimeout(connect, 2000));
    ws.addEventListener("error", () => ws.close());
    ws.addEventListener("message", ({data}) => {
        et.dispatchEvent(new CustomEvent("msg", { detail: JSON.parse(data) }));
    })
}

export function rpc(name, data) {
    return new Promise((resolve, reject) => {
        if (ws.readyState !== WebSocket.OPEN) return reject();
        const c = new AbortController();
        et.addEventListener("msg", ({ detail }) => {
            if (detail?.id !== name) return;
            detail.error ? reject(detail.error) : resolve(detail.result);
            c.abort();
        }, { signal: c.signal });

        ws.send(JSON.stringify({ id: name, method: name, params: data }));
    });
}
