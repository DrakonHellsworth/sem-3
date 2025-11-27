use("hotelDB");
db.hotel.find(
  {},
  { hotel_id: 1, name: 1, Borough: 1, cuisine: 1 }
).toArray();