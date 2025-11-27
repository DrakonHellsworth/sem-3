use("hotelDB");
db.hotel.find(
  {},
  { _id: 0, hotel_id: 1, name: 1, Borough: 1, cuisine: 1 }
).toArray();