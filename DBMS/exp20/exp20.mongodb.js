use("hotelDB");

function show(title,data){
  console.log("\n" + title);
  console.log(JSON.stringify(data,null,2));
}

show("Q1",
db.hotel.find(
  {},
  {cuisine:1,Borough:1,_id:0}
).sort({cuisine:1,Borough:-1}).toArray()
);

show("Q2",
db.hotel.find(
  {"address.street":{$exists:true}}
).toArray()
);

show("Q3",
db.hotel.find(
  {coord:{$type:"double"}}
).toArray()
);

show("Q4",
db.hotel.find(
  {"grades.score":{$mod:[7,0]}},
  {hotel_id:1,name:1,grades:1,_id:0}
).toArray()
);

show("Q5",
db.hotel.find(
  {name:/mon/i},
  {
    name:1,
    Borough:1,
    cuisine:1,
    "coord":1,
    _id:0
  }
).toArray()
);

show("Q6",
db.hotel.find(
  {name:/^mad/i},
  {
    name:1,
    Borough:1,
    cuisine:1,
    "coord":1,
    _id:0
  }
).toArray()
);
