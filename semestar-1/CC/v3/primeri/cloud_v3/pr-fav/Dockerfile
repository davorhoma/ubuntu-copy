FROM node
WORKDIR /app
COPY package*.json .
RUN npm install
COPY . .
EXPOSE 3001
ENTRYPOINT ["node"]
CMD ["app.js"]