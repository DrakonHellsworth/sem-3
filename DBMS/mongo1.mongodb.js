use("shop");

db.products.insertMany([
  { name: "Laptop", price: 55000, brand: "HP", stock: 20 },
  { name: "Phone", price: 25000, brand: "Samsung", stock: 50 },
  { name: "Headphones", price: 1500, brand: "Boat", stock: 100 }
]);
