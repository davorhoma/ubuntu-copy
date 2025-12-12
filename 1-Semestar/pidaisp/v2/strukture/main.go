package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Trougao struct {
	a float64
	b float64
	c float64
}

func (t Trougao) getPovrsina() float64 {
	s := float64(t.a+t.b+t.c) / 2
	return math.Sqrt(s * (s - t.a) * (s - t.b) * (s - t.c))
}

func main() {
	a, _ := getNumber()
	b, _ := getNumber()
	c, _ := getNumber()

	var trougao Trougao = Trougao{a, b, c}
	fmt.Printf("Povrsina trougla (%g, %g, %g) je: %.5g\n", a, b, c, trougao.getPovrsina())
}

func getNumber() (float64, error) {
	fmt.Println("Unesite duzinu stranice: ")
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Error: ", err)
		return -1, err
	}

	return strconv.ParseFloat(strings.TrimSpace(input), 64)
}
