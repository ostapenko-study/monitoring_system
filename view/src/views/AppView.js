import ProcessView from './process/ProcessView'
import ExpandedForm from './ExpandedForm';

export const AppView = ({data, totals}) => {

  return (
    <div>
      {data.pids.length === 0 ? 
        <ExpandedForm title={data.name + " (not runned)"}>
          Not runned
        </ExpandedForm>
        :
        <ExpandedForm title={data.name}>
          {data.pids.map((process) => <ProcessView data={process} totals={totals} />)}
        </ExpandedForm>
      }

    </div>
  );
};

export default AppView;