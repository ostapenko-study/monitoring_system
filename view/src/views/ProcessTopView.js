import React from "react";
import "../styles/tables.css"

const ProcessTopView = ({ processes }) => {
  return (
    <div className="table-container">
      <table className="styled-table">
        <thead>
          <tr>
            <th>PID</th>
            <th>User</th>
            <th>Command</th>
            <th>CPU %</th>
            <th>MEM %</th>
            <th>State</th>
            <th>PR</th>
            <th>NI</th>
            <th>VIRT</th>
            <th>RES</th>
            {/* <th>SHR</th> */}
            <th>Time</th>
          </tr>
        </thead>
        <tbody>
          {processes.map((proc, idx) => (
            <tr key={idx}>
              <td>{proc.pid}</td>
              <td>{proc.user}</td>
              <td>{proc.command}</td>
              <td>{proc.cpu}</td>
              <td>{proc.mem}</td>
              <td>{proc.state}</td>
              <td>{proc.pr}</td>
              <td>{proc.ni}</td>
              <td>{proc.virt}</td>
              <td>{proc.res}</td>
              {/* <td>{proc.shr}</td> */}
              <td>{proc.time}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default ProcessTopView;
