import React, { useState , useRef, useEffect} from "react";

import "../styles/box.css";

import { getRandomInt } from '../utils';

const ManagerWrapper = ({sendMessage, lastResponse, resultGenerator, formGenerator, title}) => {
  const [isRunning, setIsRunning] = useState(false);
  const [error, setError] = useState("");
  const [data, setData] = useState({})

  const indexRef = useRef(null);

  useEffect(() => {
    if (lastResponse && lastResponse.index === indexRef.current) {
      setIsRunning(false)
      if(lastResponse.isOk || lastResponse.data.isOk){
        setError("")
        setData(lastResponse)
      }else{
        setError(lastResponse.error)
      }
    }
  }, [lastResponse]);

  const handleStart = () => {
    setIsRunning(true);
    setData({});
    indexRef.current = getRandomInt()
    sendMessage({index: indexRef.current})
  };

  return (
    <div className="box">
      <div className="box-header">
        <h2>{title}</h2>
        <button
          onClick={handleStart}
          disabled={isRunning}
        >
          {isRunning ? "Виконується команда..." : "Запустити"}
        </button>
      </div>
      
      {
        formGenerator && formGenerator()
      }
      {!isRunning && (
        error !== "" ? (<div>{error}</div> ) :
        Object.keys(data).length === 0 ? <div></div> : resultGenerator(data)
      )}
    </div>
  );
};

export default ManagerWrapper;
