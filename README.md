# 💾 TECFS — TEC File System 

## 📘 Overview

**TECFS** is a custom file system simulation project developed for the course CE2103 — Algoritmos y Estructuras de Datos II at Instituto Tecnológico de Costa Rica.

The system emulates a RAID-like distributed storage model using registers, resembling a NoSQL-style data approach. Data is compressed with the Huffman algorithm and transmitted via TCP/IP sockets across multiple simulated disks. The project includes auxiliary applications for data indexing and search.

---

## 🔧 Key Components

### 🧩 RAID-Like Storage System
- Simulates multiple disks using register-based storage
- Implements Huffman compression for data transmission
- Communicates over TCP/IP (multi-client supported)
- Written in **C/C++** and executed in **Linux Mint**

### 🤖 ceROBOT
- Indexing tool for inserting books into the RAID system
- Processes folders, reads file contents, and distributes them among virtual nodes

### 🔍 ceSEARCH
- Search tool to query indexed books by keywords
- Returns a list of matching documents stored in the simulated system

---

## 🛠️ Technologies

- **Language**: C/C++
- **Platform**: Linux Mint
- **IDE**: CLion
- **Protocols**: TCP/IP Sockets
- **Compression**: Huffman encoding and decoding

---

## 📌 Notes

All components were developed and tested in **Linux Mint** using **CLion**. For additional usage instructions, see the project’s [GitHub Wiki](https://github.com/MAU143429/TECFS-CE-2103/wiki).
