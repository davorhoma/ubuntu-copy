// package main

// import (
// 	"encoding/json"
// 	"log"
// 	"net/http"

// 	"github.com/gorilla/mux"
// )

// func main() {
// 	router := mux.NewRouter()

// 	router.HandleFunc("/", func(rw http.ResponseWriter, r *http.Request) {

// 		rw.Header().Set("Content-Type", "text/plain; charset=utf-8")
// 		rw.Header().Set("Access-Control-Allow-Origin", "")
// 		rw.Header().Set("Access-Control-Max-Age", "15")

// 		response := map[string]string{
// 			"response": "Dockerizing Go Application",
// 		}

// 		json.NewEncoder(rw).Encode(response)
// 	})

// 	http.ListenAndServe(":5000", router)
// 	log.Println("[bootup]: Server is running at port: 5000")

// }

package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/rs/cors"
)

func main() {
	port := os.Getenv("PORT")
	if port == "" {
		port = "5000" // Default port if not specified
	}

	mux := http.NewServeMux()

	cors := cors.New(cors.Options{
		AllowedOrigins: []string{"*"},
		AllowedMethods: []string{
			http.MethodPost,
			http.MethodGet,
		},
		AllowedHeaders:   []string{"*"},
		AllowCredentials: false,
	})

	mux.HandleFunc("/helloThere", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/plain; charset=utf-8")
		// fmt.Fprintln(w, "General Kenobi!")
		log.Println("[info] GET : /helloThere")

		response := map[string]string{
			"response": "https://imgs.search.brave.com/QvGOqSDHPAN-ZtkM0M00PRH2OsbfoUroHgGv8YEn_6A/rs:fit:860:0:0/g:ce/aHR0cHM6Ly9wcmV2/aWV3LnJlZGQuaXQv/Z2VuZXJhbC1rZW5v/YmktbWVtZXMtdjAt/d3hlMmF3aTJtbGE5/MS5qcGc_d2lkdGg9/MzY2JmZvcm1hdD1w/anBnJmF1dG89d2Vi/cCZzPTU4ODE3NjM0/ZDQwNmYzM2MxMDcx/ZjQ1MDQ2NWZmZWFm/ZDhhMWM5NTc",
		}
		json.NewEncoder(w).Encode(response)

	})
	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		log.Println("[info] GET : /")

		w.Header().Set("Content-Type", "text/plain; charset=utf-8")

		response := map[string]string{
			"response": "Dockerizing Go Application",
		}
		json.NewEncoder(w).Encode(response)
	})
	handler := cors.Handler(mux)
	log.Println("[bootup] Server started on port " + port)
	addr := fmt.Sprintf(":%s", port)
	http.ListenAndServe(addr, handler)

}
