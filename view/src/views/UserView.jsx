import ProcessView from './process/ProcessView'
import ExpandedForm from './ExpandedForm';

export const UserView = ({data, totals}) => {

  return (
    <div>
        <ExpandedForm title={data.user + " (запущено процесів під користувачем: " + data.pids.length + ")"}>
        {data.pids.length === 0 ? 
          <div>Not runned</div>
          :
          <div>
            {data.pids
                  .filter((process) => process.name && process.name.trim() !== "")
                  .map((process) => <ProcessView key={process.pid} data={process} totals={totals} />)}

          {/* {data.pids.map((process) => <ProcessView data={process} totals={totals} />)} */}
          </div>
        }
        </ExpandedForm>
    </div>
  );
};

export default UserView;