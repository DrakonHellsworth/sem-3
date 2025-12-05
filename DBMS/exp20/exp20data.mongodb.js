use("hotelDB");

db.hotel.deleteMany({});
db.hotel.dropIndexes();

db.hotel.insertMany([
{hotel_id:"1001",name:"Royal Palace",Borough:"Bronx",cuisine:"Italian",address:{street:"Main Road",zipcode:"10420"},coord:[-73.856077,40.848447],grades:[{score:21},{score:14}]},
{hotel_id:"1002",name:"MonarchView",Borough:"Manhattan",cuisine:"Indian",address:{zipcode:"10001"},coord:[-73.955741,40.772026],grades:[{score:35},{score:7}]},
{hotel_id:"1003",name:"Ocean Morning Stay",Borough:"Queens",cuisine:"Chinese",address:{street:"Blue Lane",zipcode:"11372"},coord:[-73.977,40.75],grades:[{score:28},{score:49}]},
{hotel_id:"1004",name:"MadHouse Inn",Borough:"Brooklyn",cuisine:"Mexican",address:{street:"Red Street",zipcode:"11221"},coord:[-73.88,40.7],grades:[{score:14},{score:35}]}
]);

db.hotel.find();
