use("hotelDB19");

db.hotels.find(
  { Borough: "Bronx" }
)
.skip(5)
.limit(5)
.toArray();
