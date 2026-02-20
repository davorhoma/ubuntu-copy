package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Bank struct {
	name     string
	username string
	password string
	accounts []Account
}

func (bank Bank) toString() string {
	return fmt.Sprintf("%s,%s,%s\n", bank.name, bank.username, bank.password)
}

type Account struct {
	accNumber string
	firstName string
	lastName  string
	balance   float64
}

func (acc Account) toString() string {
	return fmt.Sprintf("%s,%s,%s,%g\n", acc.accNumber, acc.firstName, acc.lastName, acc.balance)
}

func main() {
	var banks []Bank
	loadBanks(&banks)

	var option string
	for {
		fmt.Println("---------- MENI ----------")
		fmt.Println("1: Nova banka")
		fmt.Println("2: Rad sa postojecom bankom")
		fmt.Println("X: Izlaz")

		fmt.Scanf("%s", &option)
		switch option {
		case "1":
			createBank(&banks)
		case "2":
			workWithBank(&banks)
		case "X":
			return
		case "x":
			return
		}
	}
}

func loadBanks(banks *[]Bank) {
	file, err := os.OpenFile("banks.txt", os.O_RDONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla banks.txt")
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		row := scanner.Text()
		splitted := strings.Split(row, ",")
		name := splitted[0]
		username := splitted[1]
		password := splitted[2]

		newBank := Bank{
			name:     name,
			username: username,
			password: password,
		}

		*banks = append(*banks, newBank)
	}

	// for _, bank := range *banks {
	// 	fmt.Print(bank.toString())
	// }
}

func createBank(banks *[]Bank) {
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("---------- NOVA BANKA ----------")

	fmt.Print("Unesite ime banke: ")
	scanner.Scan()
	name := scanner.Text()

	fmt.Print("Unesite username: ")
	scanner.Scan()
	username := scanner.Text()

	fmt.Print("Unesite password: ")
	scanner.Scan()
	password := scanner.Text()

	// reader := bufio.NewReader(os.Stdin)
	// fmt.Println("---------- NOVA BANKA ----------")

	// fmt.Print("Unesite ime banke: ")
	// name, _ := reader.ReadString('\n')
	// name = strings.TrimSpace(name)

	// fmt.Print("Unesite username: ")
	// username, _ := reader.ReadString('\n')
	// username = strings.TrimSpace(username)

	// fmt.Print("Unesite password: ")
	// password, _ := reader.ReadString('\n')
	// password = strings.TrimSpace(password)

	newBank := Bank{
		name:     name,
		username: username,
		password: password,
	}

	file, err := os.OpenFile("banks.txt", os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla banks.txt")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString(newBank.toString())
	writer.Flush()

	*banks = append(*banks, newBank)
}

func workWithBank(banks *[]Bank) {
	fmt.Println("---------- RAD SA POSTOJECOM BANKOM ----------")

	for {
		scanner := bufio.NewScanner(os.Stdin)
		fmt.Print("Unesite username: ")
		scanner.Scan()
		username := scanner.Text()

		fmt.Print("Unesite password: ")
		scanner.Scan()
		password := scanner.Text()

		var loggedBank *Bank
		usernamePasswordMatches := false
		for _, bank := range *banks {
			if bank.username == username && bank.password == password {
				usernamePasswordMatches = true
				loggedBank = &bank
				break
			}
		}

		if !usernamePasswordMatches {
			fmt.Println("Username and password do not match")
			continue
		}

		bankMenu(loggedBank)
		return
	}

}

func bankMenu(bank *Bank) {
	var option string

	bank.accounts = loadAccounts(bank.name + ".txt")

	fmt.Println("---------- ", bank.name, " ----------")
	fmt.Println("1: Napravi novi racun")
	fmt.Println("2: Prebaci sredstva")
	fmt.Println("X: Izlaz")
	fmt.Scanf("%s", &option)

	switch option {
	case "1":
		createAccount(bank)
	case "2":
		makeTransaction(bank)
	case "X":
		return
	case "x":
		return
	}
}

func loadAccounts(fileName string) []Account {
	file, err := os.OpenFile(fileName, os.O_RDONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla ", fileName)
		return nil
	}

	var accounts []Account
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		row := scanner.Text()
		splitted := strings.Split(row, ",")
		accNumber := splitted[0]
		firstName := splitted[1]
		lastName := splitted[2]

		balanceStr := splitted[3]
		balance, err := strconv.ParseFloat(balanceStr, 64)
		if err != nil {
			fmt.Println("Greska u parsiranju")
			return nil
		}

		newAccount := Account{
			accNumber: accNumber,
			firstName: firstName,
			lastName:  lastName,
			balance:   balance,
		}

		accounts = append(accounts, newAccount)
	}

	return accounts
}

func createAccount(bank *Bank) {
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("---------- NOVI RACUN ----------")

	fmt.Print("Unesite broj racuna: ")
	scanner.Scan()
	accNumber := scanner.Text()

	fmt.Print("Unesite ime: ")
	scanner.Scan()
	firstName := scanner.Text()

	fmt.Print("Unesite prezime: ")
	scanner.Scan()
	lastName := scanner.Text()

	fmt.Print("Unesite stanje: ")
	scanner.Scan()
	balanceStr := scanner.Text()
	balance, err := strconv.ParseFloat(balanceStr, 64)
	if err != nil {
		fmt.Println("Nije uneto validno stanje")
		return
	}

	newAccount := Account{
		accNumber: accNumber,
		firstName: firstName,
		lastName:  lastName,
		balance:   balance,
	}

	file, err := os.OpenFile(bank.name+".txt", os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla ", bank.name+".txt")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString(newAccount.toString())
	writer.Flush()

	bank.accounts = append(bank.accounts, newAccount)
}

func makeTransaction(bank *Bank) {
	if len(bank.accounts) < 2 {
		fmt.Println("Banka nema dovoljno racuna")
		return
	}

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("Unesite broj prvog racuna: ")
		scanner.Scan()
		num1 := scanner.Text()
		acc1 := findAccount(bank, num1)
		if acc1 == nil {
			return
		}

		fmt.Print("Unesite broj drugog racuna: ")
		scanner.Scan()
		num2 := scanner.Text()
		acc2 := findAccount(bank, num2)
		if acc2 == nil {
			return
		}

		fmt.Print("Unesite kolicinu sredstava za prenos: ")
		scanner.Scan()
		amountStr := scanner.Text()
		amount, err := strconv.ParseFloat(amountStr, 64)
		if err != nil {
			fmt.Println("Nevalidan amount")
			return
		}

		acc1.balance -= amount
		acc2.balance += amount
		fmt.Println(acc1.toString())

		file := openFileOverride(bank.name + ".txt")
		defer file.Close()
		if file != nil {
			fmt.Println("SAVING")
			writer := bufio.NewWriter(file)
			for _, acc := range bank.accounts {
				fmt.Println(acc.toString())
				writer.WriteString(acc.toString())
				writer.Flush()
			}
		}
	}
}

func findAccount(bank *Bank, num string) *Account {
	for i, acc := range bank.accounts {
		if acc.accNumber == num {
			return &bank.accounts[i]
		}
	}

	return nil
}

func openFileWrite(fileName string) *os.File {
	file, err := os.OpenFile(fileName, os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla ", fileName)
		return nil
	}

	return file
}

func openFileOverride(fileName string) *os.File {
	file, err := os.OpenFile(fileName, os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla ", fileName)
		return nil
	}

	return file
}

func openFileRead(fileName string) *os.File {
	file, err := os.OpenFile(fileName, os.O_RDONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla ", fileName)
		return nil
	}

	return file
}
