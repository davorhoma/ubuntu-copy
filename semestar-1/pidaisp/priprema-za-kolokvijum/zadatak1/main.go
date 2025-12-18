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

type Account struct {
	number    string
	firstName string
	lastName  string
	balance   float64
}

func (bank *Bank) toString() string {
	return fmt.Sprintf("%s,%s,%s\n", bank.name, bank.username, bank.password)
}

func (account *Account) toString() string {
	return fmt.Sprintf("%s,%s,%s,%g\n", account.number, account.firstName, account.lastName, account.balance)
}

func main() {
	var banks []Bank

	loadBanks(&banks)
	// fmt.Println("----------- BANKS -----------")
	// for _, bank := range banks {
	// 	fmt.Print(bank.toString())
	// }

	// reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Println("\n----------- MENI -----------")
		fmt.Println("1: Nova banka")
		fmt.Println("2: Login")
		fmt.Println("X: Izlaz")
		fmt.Printf("Unesite opciju: ")
		// input, _ := reader.ReadString('\n')
		var input string
		fmt.Scanf("%s", &input)
		switch input {
		case "1":
			createBank(&banks)
		case "2":
			login(&banks)
		case "X":
			return
		case "x":
			return
		}
	}
}

func loadBanks(banks *[]Bank) {
	var filePath string
	if len(os.Args) < 2 {
		filePath = "banks.txt"
	} else {
		filePath = os.Args[1]
	}

	file, err := os.OpenFile(filePath, os.O_RDONLY, 0644)
	if err != nil {
		fmt.Println("ERROR opening file ", filePath, ": ", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		value := scanner.Text()
		// fmt.Println(value)

		splitted := strings.Split(value, ",")
		bankName := splitted[0]
		username := splitted[1]
		password := splitted[2]

		existingBank := Bank{
			name:     bankName,
			username: username,
			password: password,
		}

		*banks = append(*banks, existingBank)
	}
}

func createBank(banks *[]Bank) {
	reader := bufio.NewReader(os.Stdin)
	fmt.Println("\n----------- Kreiranje nove banke -----------")
	fmt.Printf("Unesite ime banke: ")
	input, _ := reader.ReadString('\n')
	name := strings.TrimSpace(input)

	fmt.Printf("Unesite username: ")
	input, _ = reader.ReadString('\n')
	username := strings.TrimSpace(input)

	fmt.Printf("Unesite password: ")
	input, _ = reader.ReadString('\n')
	password := strings.TrimSpace(input)

	newBank := Bank{
		name:     name,
		username: username,
		password: password,
	}

	*banks = append(*banks, newBank)

	var filePath string
	if len(os.Args) < 2 {
		filePath = "banks.txt"
	} else {
		filePath = os.Args[1]
	}

	file, err := os.OpenFile(filePath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("ERROR opening file", filePath, ": ", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Println(newBank.toString())
	writer.WriteString(newBank.toString())
	err = writer.Flush()
	if err != nil {
		fmt.Println("ERROR while writing to a file: ", err)
	}
}

func login(banks *[]Bank) {
	var username string
	var password string
	var option string

	for {
		fmt.Println("\n----------- LOGIN -----------")
		fmt.Print("Yes [Y]/No [N]: ")
		fmt.Scanf("%s", &option)

		if option == "N" || option == "n" {
			return
		} else if option != "Y" && option != "y" {
			continue
		}

		fmt.Print("Username: ")
		fmt.Scanf("%s", &username)

		fmt.Print("Password: ")
		fmt.Scanf("%s", &password)

		var loggedBank Bank
		success := false
		for _, bank := range *banks {
			if bank.username == username && bank.password == password {
				loggedBank = bank
				success = true
				break
			}
		}

		if !success {
			fmt.Println("Bad credentials")
			continue
		}

		bankMenu(&loggedBank)
	}
}

func bankMenu(bank *Bank) {
	fileName := fmt.Sprintf("%s.txt", bank.name)
	file, err := os.OpenFile(fileName, os.O_RDONLY, 0644)
	if err != nil {
		fmt.Println("ERROR opening file ", fileName)
	} else {
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			row := scanner.Text()
			splitted := strings.Split(row, ",")
			number := splitted[0]
			firstName := splitted[1]
			lastName := splitted[2]
			balance, _ := strconv.ParseFloat(splitted[3], 64)

			account := Account{
				number:    number,
				firstName: firstName,
				lastName:  lastName,
				balance:   balance,
			}

			bank.accounts = append(bank.accounts, account)
		}

		file.Close()
	}

	fmt.Println("\n----------- BANK: ", bank.name, " -----------")
	var option string
	for {
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
}

func createAccount(bank *Bank) {
	reader := bufio.NewReader(os.Stdin)
	fmt.Println("\n----------- NEW ACCOUNT -----------")

	fmt.Print("Unesite broj racuna: ")
	number, _ := reader.ReadString('\n')
	number = strings.TrimSpace(number)

	fmt.Print("Unesite ime: ")
	firstName, _ := reader.ReadString('\n')
	firstName = strings.TrimSpace(firstName)

	fmt.Print("Unesite prezime: ")
	lastName, _ := reader.ReadString('\n')
	lastName = strings.TrimSpace(lastName)

	var balance float64
	var err error
	for {
		fmt.Print("Unesite kolicinu sredstava (broj): ")
		balanceStr, _ := reader.ReadString('\n')
		balanceStr = strings.TrimSpace(balanceStr)
		balance, err = strconv.ParseFloat(balanceStr, 64)
		if err == nil {
			break
		}
	}

	newAccount := Account{
		number:    number,
		firstName: firstName,
		lastName:  lastName,
		balance:   balance,
	}

	bank.accounts = append(bank.accounts, newAccount)

	file, err := os.OpenFile(fmt.Sprintf("%s.txt", bank.name), os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
	if err != nil {
		fmt.Println("ERROR opening file")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString(newAccount.toString())
	writer.Flush()
}

func makeTransaction(bank *Bank) {
	if len(bank.accounts) < 2 {
		fmt.Println("Banka nema dovoljno racuna za transakciju")
		return
	}

	fmt.Println("Izaberite dva racuna")
	for _, account := range bank.accounts {
		fmt.Println(account.number)
	}

	// var chosenAccounts []Account
	chosenAccounts := make([]Account, 0)
	reader := bufio.NewReader(os.Stdin)
	for {
		input, _ := reader.ReadString('\n')
		chosenNumber := strings.TrimSpace(input)
		for _, acc := range bank.accounts {
			if acc.number == chosenNumber {
				chosenAccounts = append(chosenAccounts, acc)
				break
			}
		}

		if len(chosenAccounts) == 2 {
			break
		}
	}

	var value float64
	fmt.Printf("Unesite kolicinu sredstava: ")
	fmt.Scanf("%g", &value)

	if chosenAccounts[0].balance < value {
		fmt.Println("Nema dovoljno sredstava na racunu ", chosenAccounts[0].number)
		return
	}

	chosenAccounts[0].balance -= value
	chosenAccounts[1].balance += value
	fmt.Println("Transakcija izvrsena")
	fmt.Println("Stanje nakon transakcije:")
	fmt.Println(chosenAccounts[0].number, " balance: ", chosenAccounts[0].balance)
	fmt.Println(chosenAccounts[1].number, " balance: ", chosenAccounts[1].balance)

	file, err := os.OpenFile(fmt.Sprintf("%s.txt", bank.name), os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("ERROR opening file")
		return
	}

	writer := bufio.NewWriter(file)
	for _, acc := range bank.accounts {
		writer.WriteString(acc.toString())
	}
	writer.Flush()
}
