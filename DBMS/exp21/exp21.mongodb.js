use("hotelDB21");

console.log("\nQ1");

console.log(
  db.hotel21.find(
    {
      cuisine:{$ne:"American"},
      "grades.score":{$gt:70},
      "address.coord.0":{$lt:-65.754168}
    },
    {_id:0,name:1,Borough:1,cuisine:1,"address.coord":1}
  ).toArray()
);

console.log("\nQ2");

console.log(
  db.hotel21.find(
    {
      cuisine:{$ne:"American"},
      "grades.grade":"A",
      Borough:{$ne:"Brooklyn"}
    },
    {_id:0,name:1,Borough:1,cuisine:1,grades:1}
  ).sort({cuisine:-1}).toArray()
);

console.log("\nQ3");

console.log(
  db.hotel21.find(
    {name:/ces$/i},
    {_id:0,id:1,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ4");

console.log(
  db.hotel21.find(
    {name:/Reg/i},
    {_id:0,id:1,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ5");

console.log(
  db.hotel21.find(
    {
      Borough:"Bronx",
      cuisine:{$in:["American","Chinese"]}
    },
    {_id:0,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ6");

console.log(
  db.hotel21.find(
    {Borough:{$in:["Staten Island","Queens","Hyatt"]}},
    {_id:0,id:1,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ7");

console.log(
  db.hotel21.find(
    {Borough:{$nin:["New Delhi","Queens","Hyatt"]}},
    {_id:0,id:1,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ8");

console.log(
  db.hotel21.find(
    {"grades.score":{$lte:10}},
    {_id:0,id:1,name:1,Borough:1,cuisine:1,grades:1}
  ).toArray()
);

console.log("\nQ9");

console.log(
  db.hotel21.find(
    {
      $or:[
        {cuisine:{$nin:["American","Chinees"]}},
        {name:/^Wil/i}
      ]
    },
    {_id:0,id:1,name:1,Borough:1,cuisine:1}
  ).toArray()
);

console.log("\nQ10");

console.log(
  db.hotel21.find(
    {
      grades:{
        $elemMatch:{
          grade:"A",
          score:11,
          date:ISODate("2014-08-11T00:00:00Z")
        }
      }
    },
    {_id:0,id:1,name:1,grades:1}
  ).toArray()
);
