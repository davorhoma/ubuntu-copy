package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	fmt.Print("N = ")
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Invalid input.")
		return
	}

	n, err := strconv.Atoi(strings.TrimSpace(input))
	if err != nil {
		fmt.Println("Please enter a valid number.")
		return
	}

	for i := 1; i < n-1; i++ {
		fmt.Print(i, ", ")
	}
	fmt.Println(n)
}
