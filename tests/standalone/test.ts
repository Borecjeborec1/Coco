type int = number;
type float = number;
type json = any;


function isPrime(x:any){
  for(let i = 2;i<x;++i){
    if(x%i==0){
      return false
    }
  }
  return x>2
}

for(let i = 0;i<100;++i){
  if(isPrime(i))
  console.log(i)
}