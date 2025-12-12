package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	number1, _ := getNumber()
	number2, _ := getNumber()

	operation, _ := getOperation()

	var result float64
	switch operation {
	case "+":
		result = number1 + number2
	case "-":
		result = number1 - number2
	case "*":
		result = number1 * number2
	case "/":
		result = number1 / number2
	case "%":
		result = number1 / number2
	default:
		fmt.Println("Not a valid operation.")
		return
	}

	fmt.Println("Result = ", result)
}

func getNumber() (float64, error) {
	reader := bufio.NewReader(os.Stdin)

	var err error = nil
	var input string
	var number1 float64
	for {
		fmt.Println("Enter a number: ")
		input, err = reader.ReadString('\n')
		if err != nil {
			fmt.Println("Error reading input: ", err)
			continue
		}

		input = strings.TrimSpace(input)
		number1, err = strconv.ParseFloat(input, 64)
		if err != nil {
			fmt.Println("Invalid input. Please enter a valid number:", err)
			continue
		}

		break
	}

	return number1, err
}

func getOperation() (string, error) {
	fmt.Println("Enter an operation:")
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Error reading input: ", err)
		return "", err
	}

	input = strings.TrimSpace(input)
	return input, err
}
