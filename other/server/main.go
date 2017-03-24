package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"sync"
	"time"

	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
	"gopkg.in/tylerb/graceful.v1"
)

const (
	ServerAddr = ":9527"
	Localhost  = "127.0.0.1"
	DBName     = "flappybird"
	Collection = "save"
)

// Packet cline format example
// http://127.0.0.1:9527/Request?value={"name":"a", "score":100}
type Packet struct {
	//Name  string `json:"name"`
	Score int    `json:"score" bson:"score"`
	GUID  string `json:"guid" bson:"guid"`
}

type ReplyPacket struct {
	Score int `json:"score"`
}

var db *mgo.Session
var scoreAry []ReplyPacket
var lock sync.Mutex

func main() {

	session, err := mgo.Dial(Localhost)
	if err != nil {
		panic(err.Error())
	}

	db = session
	scoreAry = make([]ReplyPacket, 5)

	mux := http.NewServeMux()
	mux.HandleFunc("/SaveScore", SaveScore)
	mux.HandleFunc("/TopScore", TopScore)

	srv := &graceful.Server{
		Timeout: 10 * time.Second,
		ShutdownInitiated: func() {
			fmt.Println("Server ready shutdown...")
			if db != nil {
				db.Close()
			}
		},
		//ConnState:         ConnectStateHandle,
		Server: &http.Server{
			Addr:           ServerAddr,
			ReadTimeout:    10 * time.Second,
			WriteTimeout:   10 * time.Second,
			MaxHeaderBytes: 1 << 20,
			Handler:        mux,
		},
	}

	srv.ListenAndServe()
	ShutdownHandle()
}

// ShutdownHandle -------
func ShutdownHandle() {
	fmt.Println("Server shutdown complete.")

}

// SaveScore -------
func SaveScore(w http.ResponseWriter, r *http.Request) {
	//fmt.Printf("url : %s", r.URL.String())

	value := r.FormValue("value")

	packet := new(Packet)
	json.Unmarshal([]byte(value), packet)

	if db != nil {
		c := db.DB(DBName).C(Collection)
		num, _ := c.Find(bson.M{"score": packet.Score}).Count()
		if num == 0 {
			c.Insert(packet)
			fmt.Printf("[SaveScore], value : %s\n", value)
		} else {

			fmt.Printf("[No SaveScore], value : %s\n", value)
		}
	}

}

// TopScore -------
func TopScore(w http.ResponseWriter, r *http.Request) {
	lock.Lock()
	defer lock.Unlock()

	fmt.Println("------TopScore-------")
	for i := range scoreAry {
		scoreAry[i].Score = 0
	}

	if db != nil {
		c := db.DB(DBName).C(Collection)
		query := c.Find(bson.M{}).Sort("-score")
		if query != nil {
			iter := query.Iter()
			result := new(Packet)
			for index := 0; iter.Next(result); index++ {

				if result != nil {
					fmt.Println(result)
					scoreAry[index].Score = result.Score
				}

				if index >= 4 {
					break
				}
			}
		}

	}

	byte, err := json.Marshal(scoreAry)
	if err != nil {
		panic(err.Error())
	}

	io.WriteString(w, string(byte))
}
