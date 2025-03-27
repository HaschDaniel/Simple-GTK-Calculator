# Calculator

The **Calculator** is simple GUI calculator built with GTK+ in C. It uses basic operations and functions square root and square.

## How it works

1. **Operations:** Performs addition, subtraction, multiplication, division, square root and square,
3. **Error Handling:** Displays MATH ERROR for invalid operations,
4. **GUI:** Built with GTK+, the application provides buttons for operations and displays results.

## Download

### Needed

- CMake
- GTK+ library

### Steps

1. Clone the repository:
```bash
git clone https://github.com/HaschDaniel/Simple-GTK-Calculator.git
```

2. Navigate to the project directory:
```bash
cd Simple-GTK-Calculator
```

3. Create build files using CMake:
```bash
cmake .
```

4. Build the project:
```bash
make
```

5. Run the application:
```bash
./<name-of-your-file>
```

## Usage

1. Launch the application by running `./<name-of-your-file>`,
2. Use the buttons to perform calculations:
    - Use numbers to input values,
    - Select an operator (`+`, `-`, `*`, `/`, `sqrt`, `x^2`),
    - Press `=` to compute,
    - Use `C` to reset the calculator,
3. Results are displayed on the display area.

## License

This project is open-source and available under the [Apache License 2.0](LICENSE). Feel free to use, modify, and distribute it as you want.
