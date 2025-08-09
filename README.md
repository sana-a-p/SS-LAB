# System Programming Modules

This repository contains implementations of various **system programming modules** including an assembler, macro processor, absolute loader, and relocating loader.  
Each module is organized into separate folders with corresponding C source files.

---

## 📂 Repository Structure

### 1. **Absolute Loader**
Implements the **Absolute Loader** that reads object code and loads it directly into memory without modification.

- [`loader.c`](./Absolute_Loader/loader.c) – Reads the header, verifies the program name, and loads code into simulated memory.

---

### 2. **Assembler**
Implements a **two-pass assembler** to generate object code from assembly language source.

- [`pass1.c`](./Assembler/pass1.c) – Pass 1: Builds the symbol table and calculates program length.
- [`pass2.c`](./Assembler/pass2.c) – Pass 2: Generates object code using the symbol and opcode tables.
- [`pg.c`](./Assembler/pg.c) – Alternate/combined Pass 1 assembler implementation.

---

### 3. **Macro Processor**
Implements a **macro processor** to expand macros in assembly code before assembling.

- [`macrop.c`](./Macroprocessor/macrop.c) – Reads macro definitions, stores them in tables, and expands them when encountered.

---

### 4. **Relocating Loader**
Implements a **Relocating Loader** that adjusts object code addresses when loading into memory.

- [`reloc.c`](./Relocating_Loader/reloc.c) – Parses object code, applies relocation using a bitmask, and writes adjusted addresses.

---

## 🔧 How to Compile & Run

```bash
# Example: Compile and run Absolute Loader
cd Absolute_Loader
gcc loader.c -o loader
./loader

# Example: Compile and run Assembler Pass 1
cd Assembler
gcc pass1.c -o pass1
./pass1
