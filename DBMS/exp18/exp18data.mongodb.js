use("hotelDB");

db.hotel.deleteMany({});

db.hotel.insertMany([
  {
    hotel_id: "1001",
    name: "Royal Palace",
    Borough: "Bronx",
    cuisine: "Italiana",
    address: { zipcode: "10420" }
  },
  {
    hotel_id: "1002",
    name: "Sunrise Hotel",
    Borough: "Manhattan",
    cuisine: "Indian",
    address: { zipcode: "10001" }
  },
  {
    hotel_id: "1003",
    name: "Ocean View",
    Borough: "Queens",
    cuisine: "Chinese",
    address: { zipcode: "11372" }
  }
]);

db.hotel.countDocuments();
