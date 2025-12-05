db.hotel21.drop();

db.hotel21.insertMany([
    {
        id:1,
        name:"Regency Palace",
        Borough:"Manhattan",
        cuisine:"Italian",
        address:{coord:[-66.0,40.7]},
        grades:[
            {grade:"A",score:92,date:ISODate("2014-08-11T00:00:00Z")}
        ]
    },
    {
        id:2,
        name:"MadHouse Inn",
        Borough:"Bronx",
        cuisine:"American",
        address:{coord:[-65.75,41.0]},
        grades:[
            {grade:"B",score:72,date:ISODate("2015-05-12T00:00:00Z")}
        ]
    },
    {
        id:3,
        name:"Cesar’s Place",
        Borough:"Queens",
        cuisine:"Chinese",
        address:{coord:[-70.1,39.9]},
        grades:[
            {grade:"C",score:88,date:ISODate("2015-01-01T00:00:00Z")}
        ]
    },
    {
        id:4,
        name:"Golden Arces",
        Borough:"Brooklyn",
        cuisine:"Mexican",
        address:{coord:[-72.0,38.1]},
        grades:[
            {grade:"A",score:87,date:ISODate("2016-03-03T00:00:00Z")}
        ]
    },
    {
        id:5,
        name:"Royal Hotels",
        Borough:"Hyatt",
        cuisine:"Indian",
        address:{coord:[-80.1,33.2]},
        grades:[
            {grade:"B",score:64,date:ISODate("2017-02-10T00:00:00Z")}
        ]
    },
    {
        id:6,
        name:"Palaces",
        Borough:"Staten Island",
        cuisine:"French",
        address:{coord:[-60.2,36.4]},
        grades:[
            {grade:"A",score:80,date:ISODate("2014-05-15T00:00:00Z")}
        ]
    },
    {
        id:7,
        name:"Regent House",
        Borough:"Bronx",
        cuisine:"Chinese",
        address:{coord:[-68.2,39.0]},
        grades:[
            {grade:"A+",score:95,date:ISODate("2016-09-20T00:00:00Z")}
        ]
    },
    {
        id:8,
        name:"Wilsons Diner",
        Borough:"Brooklyn",
        cuisine:"American",
        address:{coord:[-64.9,40.6]},
        grades:[
            {grade:"A",score:89,date:ISODate("2014-08-11T00:00:00Z")}
        ]
    }
]);

print("Dataset inserted.");
