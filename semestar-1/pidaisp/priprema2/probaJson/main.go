package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
	"strings"
)

type Student struct {
	Index     string     `json:"index"`
	FirstName string     `json:"firstname"`
	LastName  string     `json:"lastname"`
	Accounts  []struct{} `json:"-"`
}

func serialize(students *[]Student, filePath string) {
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla")
		return
	}

	encoder := json.NewEncoder(file)
	for _, s := range *students {
		bytes, err := json.Marshal(s)
		if err != nil {
			fmt.Println("Greska u marshallingu.")
			return
		}

		encoder.Encode(bytes)
	}
}

func serializeJSONL(students []Student, filePath string) error {
	file, err := os.OpenFile(
		filePath,
		os.O_CREATE|os.O_WRONLY|os.O_APPEND,
		0644,
	)
	if err != nil {
		return err
	}
	defer file.Close()

	encoder := json.NewEncoder(file)

	for _, s := range students {
		if err := encoder.Encode(s); err != nil {
			return err
		}
	}

	return nil
}

func deserializeJSONL(filePath string) ([]Student, error) {
	file, err := os.Open(filePath)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var students []Student
	decoder := json.NewDecoder(file)

	for decoder.More() {
		var s Student
		if err := decoder.Decode(&s); err != nil {
			return nil, err
		}
		students = append(students, s)
	}

	return students, nil
}

// func deserialize(students *[]Student, filePath string) {
// 	file, err := os.OpenFile(filePath, os.O_RDONLY, 0644)
// 	if err != nil {
// 		fmt.Println("Greska u otvaranju fajla")
// 		return
// 	}

// 	decoder := json.NewDecoder(file)
// }

func main() {
	var input string
	students := make([]Student, 0)
	deserializeMyJson(&students, "students.txt")
	for _, s := range students {
		fmt.Println(s)
	}

	for {
		fmt.Println("MENI:")
		fmt.Println("1: Unesite studenta")
		fmt.Println("X: Izlaz")

		fmt.Scanf("%s", &input)

		switch input {
		case "1":
			addStudent(&students)
		case "x":
			return
		}
	}
}

func addStudent(students *[]Student) {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Unesite broj indeksa: ")
	index, err := reader.ReadString('\n')
	index = strings.TrimSpace(index)
	if err != nil {
		return
	}

	fmt.Print("Unesite ime: ")
	firstName, err := reader.ReadString('\n')
	firstName = strings.TrimSpace(firstName)
	if err != nil {
		return
	}

	fmt.Print("Unesite prezime: ")
	lastName, err := reader.ReadString('\n')
	lastName = strings.TrimSpace(lastName)
	if err != nil {
		return
	}

	newStudent := Student{
		Index:     index,
		FirstName: firstName,
		LastName:  lastName,
	}

	*students = append(*students, newStudent)

	serializeMyJson(*students, "students.txt")
}

func serializeMyJson(students []Student, filePath string) {
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Error")
		return
	}

	defer file.Close()

	for _, s := range students {
		data, err := json.Marshal(s)
		if err != nil {
			fmt.Println("Error marshalling")
			return
		}

		_, err = file.Write(append(data, '\n'))
		if err != nil {
			fmt.Println("Error")
			return
		}
	}
}

func deserializeMyJson(students *[]Student, filePath string) {
	file, err := os.OpenFile(filePath, os.O_RDONLY, 0644)
	if err != nil {
		return
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		var student Student
		err = json.Unmarshal(scanner.Bytes(), &student)
		if err != nil {
			return
		}

		*students = append(*students, student)
	}
}
