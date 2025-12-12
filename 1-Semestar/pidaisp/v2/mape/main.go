package main

import (
	"bufio"
	"fmt"
	"os"
)

type Student struct {
	ime         string
	prezime     string
	godinaUpisa int
	prosek      float64
}

func main() {
	students := make(map[string]Student)

	for {
		fmt.Println("\nMeni:")
		fmt.Println("1: Unos novog studenta")
		fmt.Println("2: Brisanje postojeceg studenta")
		fmt.Println("X: EXIT")

		var input string
		fmt.Scanf("%s\n", &input)

		switch input {
		case "1":
			brojIndeksa, student := unesiStudenta()
			students[brojIndeksa] = student
		case "2":
			obrisiStudenta(&students)
		case "X":
			return
		case "x":
			return
		default:
		}
	}
}

func unesiStudenta() (string, Student) {
	var student Student

	for {
		var brojIndeksa string
		var err error

		reader := bufio.NewReader(os.Stdin)

		fmt.Print("Unesite broj indeksa: ")
		brojIndeksa, _ = reader.ReadString('\n')

		fmt.Println(brojIndeksa)

		fmt.Print("Unesite ime: ")
		_, err = fmt.Scanf("%s\n", &student.ime)

		fmt.Print("Unesite prezime: ")
		_, err = fmt.Scanf("%s\n", &student.prezime)

		fmt.Print("Unesite godinu upisa: ")
		_, err = fmt.Scanf("%d\n", &student.godinaUpisa)

		fmt.Print("Unesite prosek: ")
		_, err = fmt.Scanf("%g\n", &student.prosek)

		if err == nil {
			return brojIndeksa, student
		}
	}
}

func obrisiStudenta(students *map[string]Student) {
	var brojIndeksa string
	var err error

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Unesite broj indeksa: ")
	brojIndeksa, err = reader.ReadString('\n')

	if err != nil {
		fmt.Println("Pogresan broj indeksa.")
		return
	}

	delete(*students, brojIndeksa)
	fmt.Println("Obrisan student sa brojem indeksa: ", brojIndeksa)
	fmt.Println("Mapa: ", *students)
}
