package main

import (
	"fmt"
	"math"
)

type Figura interface {
	obim() float64
	povrsina() float64
}

type Trougao struct {
	a float64
	b float64
	c float64
}

type Pravouganonik struct {
	a float64
	b float64
}

func (t *Trougao) obim() float64 {
	return t.a + t.b + t.c
}

func (t *Trougao) povrsina() float64 {
	s := (t.a + t.b + t.c) / 2
	return math.Sqrt(s * (s - t.a) * (s - t.b) * (s - t.c))
}

func (p *Pravouganonik) obim() float64 {
	return 2*p.a + 2*p.b
}

func (p *Pravouganonik) povrsina() float64 {
	return p.a * p.b
}

func main() {
	var t Trougao = Trougao{
		a: 3,
		b: 4,
		c: 5,
	}

	var p Pravouganonik = Pravouganonik{
		a: 3,
		b: 4,
	}

	fmt.Println("Obim T: ", t.obim())
	fmt.Println("Povrsina T: ", t.povrsina())

	fmt.Println("Obim P: ", p.obim())
	fmt.Println("Povrsina P: ", p.povrsina())
}
