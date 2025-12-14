package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Student struct {
	brojIndeksa string
	ime         string
	prezime     string
	prosek      float64
}

func (s *Student) toString() string {
	return fmt.Sprintf("%s %s %s %g", s.brojIndeksa, s.ime, s.prezime, s.prosek)
}

func (s *Student) serialize() string {
	return fmt.Sprintf("%s,%s,%s,%g", s.brojIndeksa, s.ime, s.prezime, s.prosek)
}

func deserialize(line string) Student {
	splitted := strings.Split(line, ",")
	prosek, _ := strconv.ParseFloat(splitted[3], 64)
	return Student{
		brojIndeksa: splitted[0],
		ime:         splitted[1],
		prezime:     splitted[2],
		prosek:      prosek,
	}
}

func main() {
	var students []Student

	var filePath string
	if len(os.Args) == 2 {
		filePath = os.Args[1]
	}
	file, err := os.OpenFile(filePath, os.O_RDONLY, os.ModeExclusive)
	if err != nil {
		fmt.Println("Error opening file: ", filePath)
	} else {
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			s := deserialize(scanner.Text())
			students = append(students, s)
		}
	}

	menu(&students)
}

func menu(students *[]Student) {
	for {
		fmt.Println("MENI:")
		fmt.Println("1: Unos novog studenta")
		fmt.Println("2: Ispis svih studenata po proseku")
		fmt.Println("3: Ukupan prosek svih studenata")
		fmt.Println("X: EXIT")

		var option string
		fmt.Scanf("%s", &option)
		switch option {
		case "1":
			newStudent(students)
		case "2":
			showStudents(students)
		case "3":
			showAllAverageGrade(students)
		case "X":
			return
		case "x":
			return
		}
	}
}

func newStudent(students *[]Student) {
	var brojIndeksa string
	var ime string
	var prezime string
	var prosek float64

	reader := bufio.NewReader(os.Stdin)
	fmt.Println("---------- NOVI STUDENT ------------")
	fmt.Print("Unesite broj indeksa: ")
	brojIndeksa, _ = reader.ReadString('\n')
	brojIndeksa = strings.TrimSpace(brojIndeksa)

	for _, s := range *students {
		if s.brojIndeksa == brojIndeksa {
			fmt.Println("Student sa brojem indeksa: ", brojIndeksa, " vec postoji")
			return
		}
	}

	fmt.Print("Unesite ime: ")
	fmt.Scanf("%s", &ime)

	fmt.Print("Unesite prezime: ")
	fmt.Scanf("%s", &prezime)

	fmt.Print("Unesite prosecnu ocenu: ")
	fmt.Scanf("%g", &prosek)

	newStudent := Student{
		brojIndeksa: brojIndeksa,
		ime:         ime,
		prezime:     prezime,
		prosek:      prosek,
	}
	*students = append(*students, newStudent)

	var args []string = os.Args
	var filePath string
	if len(args) == 2 {
		filePath = args[1]
	} else {
		return
	}

	file, err := os.OpenFile(filePath, os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla")
		return
	}
	defer file.Close()
	writer := bufio.NewWriter(file)
	_, err = writer.WriteString(newStudent.serialize() + "\n")
	if err != nil {
		log.Fatal(err)
	}
	_ = writer.Flush()
}

func showStudents(students *[]Student) {
	var sortBy string
	fmt.Println("A - ascending, D - descending")
	fmt.Scanf("%s", &sortBy)

	switch strings.ToUpper(sortBy) {
	case "A":
		sortedStudents := make([]Student, len(*students))
		copy(sortedStudents, *students)
		sort.Slice(sortedStudents, func(i, j int) bool {
			return sortedStudents[i].prosek < sortedStudents[j].prosek
		})

		fmt.Print("\n")
		for _, s := range sortedStudents {
			fmt.Println(s.toString())
		}
		fmt.Print("\n")
	case "D":
		sortedStudents := make([]Student, len(*students))
		copy(sortedStudents, *students)
		sort.Slice(sortedStudents, func(i, j int) bool {
			return sortedStudents[i].prosek > sortedStudents[j].prosek
		})

		fmt.Print("\n")
		for _, s := range sortedStudents {
			fmt.Println(s.toString())
		}
		fmt.Print("\n")
	default:
		fmt.Println("DEFAULT: ", sortBy)
	}
}

func showAllAverageGrade(students *[]Student) {
	var ukupanProsek float64
	var brojNula int
	for _, s := range *students {
		if s.prosek == 0 {
			brojNula++
		}
		ukupanProsek += s.prosek
	}

	ukupanProsek /= float64(len(*students) - brojNula)

	fmt.Println("Ukupan prosek svih studenata: ", ukupanProsek)
}
