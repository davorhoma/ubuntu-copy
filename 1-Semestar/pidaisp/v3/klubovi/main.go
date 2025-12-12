package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"
)

type Klub struct {
	naziv           string
	skraceniNaziv   string
	godinaOsnivanja int
}

func (k *Klub) toString() string {
	return fmt.Sprintf("%s,%s,%d\n", k.naziv, k.skraceniNaziv, k.godinaOsnivanja)
}

func deserialize(row string) Klub {
	values := strings.Split(row, ",")
	godOsn, _ := strconv.Atoi(values[2])
	return Klub{
		naziv:           values[0],
		skraceniNaziv:   values[1],
		godinaOsnivanja: godOsn,
	}
}

func noviKlub(naziv, skraceniNaziv string, godOsn int) Klub {
	return Klub{
		naziv:           naziv,
		skraceniNaziv:   skraceniNaziv,
		godinaOsnivanja: godOsn,
	}
}

const kluboviFile = "klubovi.txt"
const meceviFile = "mecevi.txt"

func main() {
	var n int
	fmt.Print("Unesite N: ")
	fmt.Scanf("%d", &n)

	reader := bufio.NewReader(os.Stdin)
	klubovi := make([]Klub, 0)

	file, err := os.OpenFile(kluboviFile, os.O_RDWR, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla.")
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		klub := deserialize(scanner.Text())
		klubovi = append(klubovi, klub)
	}

	writer := bufio.NewWriter(file)

	for _ = range n {
		fmt.Print("Unesite naziv kluba: ")
		naziv, _ := reader.ReadString('\n')
		naziv = strings.TrimSpace(naziv)

		var duplicate bool = false
		for _, k := range klubovi {
			if naziv == k.naziv {
				fmt.Println("Naziv kluba mora biti jedinstven.")
				duplicate = true
				break
			}
		}

		if duplicate {
			continue
		}

		fmt.Print("Unesite skraceni naziv kluba: ")
		skraceniNaziv, _ := reader.ReadString('\n')
		skraceniNaziv = strings.TrimSpace(skraceniNaziv)

		fmt.Print("Unesite godinu osnivanja: ")
		var godOsn int
		fmt.Scanf("%d", &godOsn)

		klub := noviKlub(naziv, skraceniNaziv, godOsn)
		klubovi = append(klubovi, klub)

		writer.WriteString(klub.toString())
		writer.Flush()
	}

	file.Close()
	generisiUtakmice(klubovi)
}

func generisiUtakmice(klubovi []Klub) {
	// mecevi := make([]Mec, 0)

	var numOfRoutines int = 0
	if len(os.Args) > 1 {
		value, err := strconv.Atoi(os.Args[1])
		if err != nil {
			numOfRoutines = 4
		} else {
			numOfRoutines = value
		}
	} else {
		numOfRoutines = 4
	}

	c := make(chan Mec, 100)
	var wg sync.WaitGroup

	// podela slice-a ravnomerno
	chunkSize := (len(klubovi) + numOfRoutines - 1) / numOfRoutines

	for i := 0; i < numOfRoutines; i++ {
		start := i * chunkSize
		end := start + chunkSize
		if end > len(klubovi) {
			end = len(klubovi)
		}
		if start >= len(klubovi) {
			break
		}

		wg.Add(1)
		go generateByRoutine(klubovi[start:end], klubovi, c, &wg)
	}

	// for _, domacaEkipa := range klubovi {
	// 	for _, gostujucaEkipa := range klubovi {
	// 		if domacaEkipa.naziv == gostujucaEkipa.naziv {
	// 			continue
	// 		}

	// 		startTime := time.Date(2025, 1, 1, 11, 0, 0, 0, time.UTC)
	// 		endTime := time.Date(2025, 12, 31, 20, 0, 0, 0, time.UTC)
	// 		mec := Mec{
	// 			id:              strconv.Itoa(rand.Int()),
	// 			domacaEkipa:     domacaEkipa.skraceniNaziv,
	// 			gostujucaEkipa:  gostujucaEkipa.skraceniNaziv,
	// 			vremeOdrzavanja: generateRandomTime(startTime, endTime),
	// 			rezultat:        generateRandomResult(50 / len(klubovi)),
	// 		}

	// 		mecevi = append(mecevi, mec)
	// 	}
	// }

	go func() {
		wg.Wait()
		close(c)
	}()

	file, err := os.OpenFile(meceviFile, os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println("Greska u otvaranju fajla: ", meceviFile)
		return
	}

	writer := bufio.NewWriter(file)
	// for _, mec := range mecevi {
	// 	fmt.Println("WRITTING MATCH ", mec.domacaEkipa)
	// 	writer.WriteString(mec.toString())
	// 	writer.Flush()
	// }
	for mec := range c {
		fmt.Println("WRITTING MATCH ", mec.domacaEkipa)
		writer.WriteString(mec.toString())
		writer.Flush()
	}
}

func generateByRoutine(klubovi []Klub, sviKlubovi []Klub, c chan Mec, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Println("klubovi.size: ", len(klubovi))
	for _, domacaEkipa := range klubovi {
		for _, gostujucaEkipa := range sviKlubovi {
			if domacaEkipa.naziv == gostujucaEkipa.naziv {
				continue
			}

			startTime := time.Date(2025, 1, 1, 11, 0, 0, 0, time.UTC)
			endTime := time.Date(2025, 12, 31, 20, 0, 0, 0, time.UTC)
			mec := Mec{
				id:              strconv.Itoa(rand.Int()),
				domacaEkipa:     domacaEkipa.skraceniNaziv,
				gostujucaEkipa:  gostujucaEkipa.skraceniNaziv,
				vremeOdrzavanja: generateRandomTime(startTime, endTime),
				rezultat:        generateRandomResult(50 / len(sviKlubovi)),
			}

			// mecevi = append(mecevi, mec)
			c <- mec
		}
	}

	fmt.Println("DONE")
}

func generateRandomTime(start, end time.Time) time.Time {
	rand.Seed(time.Now().UnixNano())

	minUnix := start.Unix()
	maxUnix := end.Unix()

	delta := maxUnix - minUnix

	randomSeconds := rand.Int63n(delta)

	randomUnix := minUnix + randomSeconds

	return time.Unix(randomUnix, 0)
}
