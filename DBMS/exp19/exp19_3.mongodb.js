use("hotelDB19");

db.hotels.find(
  { latitude: { $lt: -95.75 } }
).toArray();
