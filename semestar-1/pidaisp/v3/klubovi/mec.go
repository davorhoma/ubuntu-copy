package main

import (
	"fmt"
	"math/rand"
	"time"
)

type Mec struct {
	id              string
	domacaEkipa     string
	gostujucaEkipa  string
	vremeOdrzavanja time.Time
	rezultat        string
}

func (mec *Mec) toString() string {
	return fmt.Sprintf("%s,%s,%s,%s,%s\n", mec.id, mec.domacaEkipa, mec.gostujucaEkipa, mec.vremeOdrzavanja.Format("2006-01-02 15:04"), mec.rezultat)
}

func generateRandomResult(goalsPerMatch int) string {
	team1 := rand.Intn(goalsPerMatch)
	// team2 := rand.Intn(10 - team1)
	team2 := goalsPerMatch - team1

	return fmt.Sprintf("%d:%d", team1, team2)
}
