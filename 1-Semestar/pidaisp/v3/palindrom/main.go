package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	fmt.Print("Unesite recenicu: ")
	reader := bufio.NewReader(os.Stdin)
	recenica, _ := reader.ReadString('\n')
	if len(recenica)%2 != 0 {
		fmt.Println("Recenica mora imati neparan broj slova.")
		return
	}

	recenica = strings.TrimSpace(recenica)
	palindrom := createPalindrom(recenica)
	fmt.Println("Palindrom od unete recenice:\n", palindrom)
}

func createPalindrom(recenica string) string {
	length := len(recenica)
	for i := length - 2; i >= 0; i-- {
		recenica = fmt.Sprintf("%s%c", recenica, recenica[i])
	}

	return recenica
}
