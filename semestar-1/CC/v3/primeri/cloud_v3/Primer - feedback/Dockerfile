FROM node:14
WORKDIR /app
COPY package.json .
RUN npm install
COPY . .

# EXPOSE 3001 sluzi samo za dokumentaciju. Nema nikakav uticaj na mapiranje portova. Samo da bi bilo lakse ostalima da znaju na kom portu je planirano pokrenuti ovu app
EXPOSE 3001

# VOLUME pravi anonimni volume, ali je problem sto se taj volume pravi svaki put prilikom pokretanja kontejnera i nije uvezan sa njim.
# VOLUME ["/app/feedback"]

ENTRYPOINT ["node", "server.js"]