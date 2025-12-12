package main

import (
	"fmt"
	"testing"
)

func TestPalindrom(t *testing.T) {
	palindrom := createPalindrom("Ana voliM")
	fmt.Println(palindrom)
	for i, j := 0, len(palindrom)-1; i < len(palindrom)/2; i++ {
		if palindrom[i] != palindrom[j] {
			t.Errorf("Function doesn't work as planned.")
		}
		j--
	}
}
