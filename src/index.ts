import { DurableObject } from "cloudflare:workers";
import { Hono } from "hono";

export class App extends DurableObject {
  private app = new Hono()
    .get("/api/status", (c) => c.json({ ok: true, device: "CYD-ESP32" }));

  async fetch(request: Request) {
    return this.app.fetch(request);
  }
}
