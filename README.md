# AdvancedShare – Offline P2P File Transfer (CLI)

AdvancedShare is a fast, offline, peer-to-peer file transfer tool designed for nearby devices on the same network or hotspot.
It works without internet, cloud servers, or accounts.

This repository currently contains **ALPHA (v0.1)** — a working but minimal version focused on core reliability.

---

## 🚀 Features (Alpha v0.1)

- Direct sender ↔ receiver file transfer
- Works completely offline (same Wi-Fi / hotspot)
- Accept / Reject system before transfer
- Live progress percentage
- Real-time speed display
- ETA (estimated time remaining)
- Large file support (GBs)
- Simple CLI-based usage

---

## 🛠️ Tech Stack

- Language: **C++**
- Networking: **TCP sockets**
- Platform: **Windows (tested)**  
  *(Linux/macOS planned)*

---

## 📦 How It Works (High Level)

1. Receiver runs in listen mode
2. Sender connects and sends file metadata
3. Receiver accepts or rejects
4. On acceptance:
   - File is sent in chunks
   - Progress, speed, and ETA are shown
5. Transfer completes

No server. No cloud. No internet.
