use("hotelDB19");

db.hotels.find(
  { "grades.score": { $gt: 80, $lt: 100 } }
).toArray();
