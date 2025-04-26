import React, { useState , useRef, useEffect} from "react";
import ProcessTopView from "./ProcessTopView";

import "../../styles/box.css";

import { getRandomInt } from './../../utils';

const ProcessTopManager = ({sendMessage, lastResponse, ip}) => {
  const [isRunning, setIsRunning] = useState(false);
  const [processes, setProcesses] = useState([]);

  const indexRef = useRef(null);

  useEffect(() => {
    if (lastResponse && lastResponse.index === indexRef.current) {
      setIsRunning(false)
      setProcesses(lastResponse.top)
    }
  }, [lastResponse]);

  const handleStart = () => {
    setIsRunning(true);
    setProcesses([]); 
    indexRef.current = getRandomInt()
    sendMessage({command: "get_top_by_ssh", data: {ip: ip}, index: indexRef.current})
  };

  return (
    <div className="box">
      <div className="box-header">
        <h2>Перелік процесів</h2>
        <button
          onClick={handleStart}
          disabled={isRunning}
        >
          {isRunning ? "Виконується команда..." : "Запустити"}
        </button>
      </div>
      {!isRunning && (
        processes.length > 0 ? (
          <ProcessTopView processes={processes} />
        ) : (
          <div>Запит (якщо був) повернув пусту відповідь</div>
        )
      )}
    </div>
  );
};

export default ProcessTopManager;
