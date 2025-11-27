use("hotelDB19");

db.hotels.find(
  {
    cuisine: { $ne: "American" },
    "grades.score": { $gt: 70 },
    latitude: { $lt: 65.754168 }
  }
).toArray();
