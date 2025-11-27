use("hotelDB19");

db.hotels.deleteMany({});

db.hotels.insertMany([
  {
    hotel_id: "2001",
    name: "Royal Palace",
    Borough: "Bronx",
    cuisine: "Italian",
    latitude: -96.20,
    grades: [{ score: 85 }]
  },
  {
    hotel_id: "2002",
    name: "Sunrise Hotel",
    Borough: "Bronx",
    cuisine: "Chinese",
    latitude: -97.50,
    grades: [{ score: 92 }]
  },
  {
    hotel_id: "2003",
    name: "Ocean View",
    Borough: "Manhattan",
    cuisine: "American",
    latitude: 40.71,
    grades: [{ score: 88 }]
  },
  {
    hotel_id: "2004",
    name: "Palm Residency",
    Borough: "Bronx",
    cuisine: "Mexican",
    latitude: -95.60,
    grades: [{ score: 75 }]
  },
  {
    hotel_id: "2005",
    name: "Green Leaf Inn",
    Borough: "Bronx",
    cuisine: "Indian",
    latitude: -98.10,
    grades: [{ score: 95 }]
  },
  {
    hotel_id: "2006",
    name: "Silver Star",
    Borough: "Queens",
    cuisine: "Thai",
    latitude: 60.22,
    grades: [{ score: 72 }]
  },
  {
    hotel_id: "2007",
    name: "Hotel Paradise",
    Borough: "Bronx",
    cuisine: "Continental",
    latitude: 64.12,
    grades: [{ score: 82 }]
  },
  {
    hotel_id: "2008",
    name: "Lakeview Hotel",
    Borough: "Bronx",
    cuisine: "Italian",
    latitude: -96.70,
    grades: [{ score: 89 }]
  },
  {
    hotel_id: "2009",
    name: "Horizon Stay",
    Borough: "Bronx",
    cuisine: "Indian",
    latitude: -96.95,
    grades: [{ score: 78 }]
  },
  {
    hotel_id: "2010",
    name: "Comfort Suites",
    Borough: "Bronx",
    cuisine: "Turkish",
    latitude: -97.25,
    grades: [{ score: 99 }]
  }
]);

db.hotels.countDocuments();
